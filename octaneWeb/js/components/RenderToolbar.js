/**
 * RenderToolbar.js - Official Octane-style render toolbar component
 * Based on official Octane Standalone documentation with exact tooltips and functionality
 * Includes gRPC integration placeholders for real Octane API calls
 */

class RenderToolbar {
    constructor(containerId, octaneClient = null) {
        this.container = document.getElementById(containerId);
        this.client = octaneClient; // Reference to OctaneWebClient for gRPC calls
        this.renderStats = {
            samples: 17.1,
            time: '00:00:00',
            status: 'finished',
            resolution: '1920x1080',
            meshCount: 1,
            gpu: 'NVIDIA GeForce RTX 4090 (RT)',
            version: '1.48.21.224.4',
            memory: 'GB'
        };
        
        // Toolbar state
        this.realTimeMode = false;
        this.viewportLocked = false;
        this.clayMode = false;
        this.subSampling = 'none'; // 'none', '2x2', '4x4'
        this.renderPriority = 'normal'; // 'low', 'normal', 'high'
        this.currentPickingMode = 'none'; // 'none', 'focus', 'whiteBalance', 'material', 'object', 'cameraTarget', 'renderRegion', 'filmRegion'
        this.decalWireframe = false;
        this.worldCoordinateDisplay = true;
        this.objectControlMode = 'world'; // 'world', 'local'
        this.activeGizmo = 'none'; // 'none', 'translate', 'rotate', 'scale'
        this.viewportResolutionLock = false;
        
        this.init();
    }
    
    init() {
        this.createRenderStatsBar();
        this.createRenderToolbar();
        this.updateRenderStats();
    }
    
    /**
     * Helper method to make gRPC calls through the proxy
     * @param {string} service - The gRPC service name (e.g., 'ApiRenderEngine')
     * @param {string} method - The method name (e.g., 'stopRendering')
     * @param {Object} params - Parameters to send (optional)
     * @returns {Promise} - The gRPC response
     */
    async makeGrpcCall(service, method, params = {}) {
        if (!this.client) {
            console.warn(`⚠️ No client available for gRPC call: ${service}.${method}`);
            return null;
        }
        
        try {
            console.log(`🔌 Making gRPC call: ${service}.${method}`, params);
            
            // Use the client's serverUrl to make the call
            const url = `${this.client.serverUrl}/${service}/${method}`;
            
            const response = await fetch(url, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                    'X-Call-Id': `render-toolbar-${Date.now()}`
                },
                body: JSON.stringify(params)
            });
            
            if (!response.ok) {
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            }
            
            const result = await response.json();
            console.log(`✅ gRPC call successful: ${service}.${method}`, result);
            return result;
            
        } catch (error) {
            console.error(`❌ gRPC call failed: ${service}.${method}`, error);
            return null;
        }
    }
    
    createRenderStatsBar() {
        const statsBar = document.createElement('div');
        statsBar.className = 'render-stats-bar';
        statsBar.innerHTML = `
            <div class="render-stats-left">
                <span id="render-samples-display">${this.renderStats.samples} spp</span>
                <span class="stats-separator">,</span>
                <span id="render-time-display">${this.renderStats.time}</span>
                <span id="render-status-display" class="render-status-${this.renderStats.status}">(${this.renderStats.status})</span>
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
        
        const toolbarIcons = this.createToolbarIcons();
        toolbar.appendChild(toolbarIcons);
        
        this.container.appendChild(toolbar);
    }
    
    createToolbarIcons() {
        const iconsContainer = document.createElement('div');
        iconsContainer.className = 'render-toolbar-icons';
        
        // Official Octane render viewport controls based on documentation
        const icons = [
            // Camera & View Controls
            { id: 'recenter-view', icon: '⌖', tooltip: 'Recenter View - Centers the render view display area in the Render Viewport. This is useful if you move the render view display area and part of it is no longer visible or centered. This re-centers the render view display area without affecting the current zoom level.' },
            { id: 'reset-camera', icon: '⌂', tooltip: 'Reset Camera - Resets the camera back to the original position. If you create a scene from an imported object, then the Camera Reset button resets the camera position to the default coordinates, similar to when the object was just imported.' },
            { id: 'camera-presets', icon: '📷', tooltip: 'Camera View Presets - Provides preset camera views of the scene in the Render Viewport.' },
            
            { type: 'separator' },
            
            // Render Controls
            { id: 'stop-render', icon: '■', tooltip: 'Stop Render - Aborts the rendering process and frees all resources used by the current scene.', important: true },
            { id: 'restart-render', icon: '↻', tooltip: 'Restart Render - Halts the current rendering process while keeping the loaded contents in memory, and then restarting the rendering process at zero samples.', important: true },
            { id: 'pause-render', icon: '⏸', tooltip: 'Pause Render - Pauses the rendering process without losing the rendered data, and also keeps the contents of the GPU\'s memory intact. Pausing the render is useful when you need to free the GPU cores in order to run other GPU-intensive applications, and intend to continue the render process later.' },
            { id: 'start-render', icon: '▶', tooltip: 'Start Render - Starts the rendering process, or resumes the render from the point where it was paused.', important: true },
            { id: 'real-time-render', icon: '⚡', tooltip: 'Real Time Rendering - Uses more GPU memory to provide a more interactive experience. Note that some features do not work when this button is active.' },
            
            { type: 'separator' },
            
            // Picking Tools
            { id: 'focus-picker', icon: '◎', tooltip: 'Auto Focus Picking Mode - Helps with navigating complex or difficult scenes. To enter Focus Picking mode, click on the Focus Picking icon under the Render Viewport, then click on any part of the scene to focus the camera on that point. When enabled, right-clicking on the mouse brings up a context menu for picking objects along the path of a ray, affecting that point in the scene.' },
            { id: 'white-balance-picker', icon: '⚪', tooltip: 'White Balance Picking Mode - Selects any part of the scene to see white point colors applicable to the whole scene on the basis of a diffuse within the scene. This does not cause the render to restart, as the current white point color is used throughout the render. To restore the scene\'s original balance, click on an empty part of the scene while in this mode.' },
            { id: 'material-picker', icon: '●', tooltip: 'Material Picker - Select any part of the rendered scene to inspect the material applied to it. Right-clicking on the mouse when this is enabled invokes a context menu to pick materials applied to the objects along the path of a ray, affecting that point in the scene. OctaneRender® invokes the Material node and it appears on the Node Inspector.' },
            { id: 'object-picker', icon: '▢', tooltip: 'Object Picker - Select particular objects in the rendered scene to inspect its attributes on the Node Inspector pane. Right-clicking the mouse when this is enabled brings up a context menu to pick of the objects along the path of a ray, affecting that point in the scene. The object\'s node graph representation is also selected on the Graph Editor.' },
            { id: 'camera-target-picker', icon: '⊙', tooltip: 'Camera Target Picker - Helps with navigating a scene that is very complex or is difficult to navigate. To enter Camera Target Zoom Picking mode, click on the Camera Target Zoom Picking icon under the Render Viewport, then click on any part of the scene to make the point under the mouse pointer become the center of rotation and zooming. A quick roll of the mouse wheel causes the render to zoom in to the selected point.' },
            
            { type: 'separator' },
            
            // Region Tools
            { id: 'render-region-picker', icon: '◊', tooltip: 'Render Region Picker - Specifies a region in the Viewport to view changes and reduce noise in specific areas. To use Render Region Picking mode, click on the Render Region Picking icon under the Render Viewport, then select a rectangular area in the Viewport to restrict rendering to that area. A feathered border represents the selected area. To disable this feature and return to rendering the whole image, click once anywhere in the Viewport.' },
            { id: 'film-region-picker', icon: '▭', tooltip: 'Film Region Picker - Specifies a region in the scene to set new values for Region Start and Region Size for Film Settings parameters, which configures the render film. Although the resolution remains the same, just the film region gets rendered. You can reset the film region back to its full size by double-clicking on the Render Viewport while the toggle is enabled.' },
            
            { type: 'separator' },
            
            // Rendering Settings
            { id: 'clay-mode', icon: '◐', tooltip: 'Clay Mode Rendering Settings - Shows the model details while rendering is still in progress. This lets you see details without the complex texturing applied, or colors and/or textures to be applied.' },
            { id: 'subsample-2x2', icon: '▦', tooltip: 'Sub-Sampling Settings 2×2 - Provides smoother scene navigation by reducing the render resolution. In order to improve navigation at the cost of visual quality, you can adjust 2×2 sub-sampling settings by using the checkerboard buttons under the Render Viewport. The reduced settings apply when navigating the scene, and then it returns to the render settings after stopping navigation.' },
            { id: 'subsample-4x4', icon: '▣', tooltip: 'Sub-Sampling Settings 4×4 - Provides smoother scene navigation by reducing the render resolution. In order to improve navigation at the cost of visual quality, you can adjust 4×4 sub-sampling settings by using the checkerboard buttons under the Render Viewport. The reduced settings apply when navigating the scene, and then it returns to the render settings after stopping navigation.' },
            { id: 'decal-wireframe', icon: '🔲', tooltip: 'Decal Wireframe Boundaries - Toggles wireframe along the boundaries of the decals.' },
            { id: 'render-priority', icon: '⚙', tooltip: 'Render Priority Settings - This sets the priority for the active GPUs when the Use Priority option is enabled on the Devices preferences tab. The render priority is necessary when a GPU is not dedicated to rendering, but is also shared among different processes in one machine. For example, a machine that has one GPU shares the GPU for processes across the whole system, including the operating system.' },
            
            { type: 'separator' },
            
            // Output Controls
            { id: 'copy-clipboard', icon: '📋', tooltip: 'Copy to Clipboard - Copies the current rendered image to the clipboard in low dynamic range format, which you can paste in to different applications.' },
            { id: 'save-render', icon: '💾', tooltip: 'Save Render - Saves the current render to disk in a specific file format.' },
            { id: 'export-passes', icon: '📤', tooltip: 'Export Render Passes - Brings up the Render Passes Export window.' },
            { id: 'background-image', icon: '🖼', tooltip: 'Set Background Image - Places a background image in the Render Viewport. To see the background image, enable the Alpha Channel for the Kernel.' },
            
            { type: 'separator' },
            
            // Viewport Controls
            { id: 'viewport-resolution-lock', icon: '🔒', tooltip: 'Viewport Resolution Lock - The Viewport can scroll up and down to accommodate the rendered image\'s current visible size. Enabling this facility adjusts the resolution of the rendered image to the current Viewport size. If this is enabled, OctaneRender® restarts the rendering every time you adjust the Viewport window\'s size, since the image resolution also changes.' },
            { id: 'lock-viewport', icon: '🔐', tooltip: 'Lock Viewport - Locks and unlocks the Viewport controls. Locking the Viewport controls prevents accidental changes or render restarts.' },
            
            { type: 'separator' },
            
            // Object Manipulation
            { id: 'object-control-alignment', icon: '🌐', tooltip: 'Object Control Alignment Mode - Specifies the coordinate system used while modifying Placement and Scatter nodes using handles for rotation, scaling, and translation in the Viewport. You can choose to align with the world axis, or with the local axis while working with the gizmos for object controls.' },
            { id: 'translate-gizmo', icon: '↔', tooltip: 'Placement Translation Tool (Toggle Move Gizmo) - Modifies the translation of Placement and Scatter nodes using handles in the Viewport. The Move tool allows movement along each axis, or constrained to the plane defined by two axes using different parts of the control.' },
            { id: 'rotate-gizmo', icon: '🔄', tooltip: 'Placement Rotation Tool (Toggle Rotate Gizmo) - Modifies the rotation of Placement and Scatter nodes using handles in the Viewport. The Rotation tool allows rotation around each axis via the axis rotation bands, a free rotation via the inner orange circle, and rotation around the camera-object axis via the outer yellow circle.' },
            { id: 'scale-gizmo', icon: '⚖', tooltip: 'Placement Scale Tool (Toggle Scale Gizmo) - Adjusts the scale of Placement and Scatter nodes using handles in the Viewport. The Scale tool works along each axis by selecting one of the axis lines, constrained to two axes by selecting one of the corners near the origin, and uniform scaling works by selecting one of the axis end handles.' },
            { id: 'world-coordinate', icon: '🧭', tooltip: 'Display World Coordinate - This displays a small representation of the World Coordinate axis at the top-left corner of the Viewport.' }
        ];
        
        icons.forEach(iconData => {
            if (iconData.type === 'separator') {
                const separator = document.createElement('div');
                separator.className = 'toolbar-separator';
                iconsContainer.appendChild(separator);
            } else {
                const button = document.createElement('button');
                button.className = `toolbar-icon-btn ${iconData.important ? 'important' : ''} ${this.getButtonActiveClass(iconData.id)}`;
                button.id = iconData.id;
                button.innerHTML = iconData.icon;
                button.title = iconData.tooltip;
                button.addEventListener('click', () => this.handleToolbarAction(iconData.id));
                iconsContainer.appendChild(button);
            }
        });
        
        return iconsContainer;
    }
    
    getButtonActiveClass(buttonId) {
        switch (buttonId) {
            case 'real-time-render':
                return this.realTimeMode ? 'active' : '';
            case 'lock-viewport':
                return this.viewportLocked ? 'active' : '';
            case 'clay-mode':
                return this.clayMode ? 'active' : '';
            case 'subsample-2x2':
                return this.subSampling === '2x2' ? 'active' : '';
            case 'subsample-4x4':
                return this.subSampling === '4x4' ? 'active' : '';
            case 'decal-wireframe':
                return this.decalWireframe ? 'active' : '';
            case 'viewport-resolution-lock':
                return this.viewportResolutionLock ? 'active' : '';
            case 'object-control-alignment':
                return this.objectControlMode === 'world' ? 'active' : '';
            case 'translate-gizmo':
                return this.activeGizmo === 'translate' ? 'active' : '';
            case 'rotate-gizmo':
                return this.activeGizmo === 'rotate' ? 'active' : '';
            case 'scale-gizmo':
                return this.activeGizmo === 'scale' ? 'active' : '';
            case 'world-coordinate':
                return this.worldCoordinateDisplay ? 'active' : '';
            case 'focus-picker':
                return this.currentPickingMode === 'focus' ? 'active' : '';
            case 'white-balance-picker':
                return this.currentPickingMode === 'whiteBalance' ? 'active' : '';
            case 'material-picker':
                return this.currentPickingMode === 'material' ? 'active' : '';
            case 'object-picker':
                return this.currentPickingMode === 'object' ? 'active' : '';
            case 'camera-target-picker':
                return this.currentPickingMode === 'cameraTarget' ? 'active' : '';
            case 'render-region-picker':
                return this.currentPickingMode === 'renderRegion' ? 'active' : '';
            case 'film-region-picker':
                return this.currentPickingMode === 'filmRegion' ? 'active' : '';
            default:
                return '';
        }
    }
    
    handleToolbarAction(actionId) {
        console.log(`🎬 Octane Toolbar Action: ${actionId}`);
        
        switch (actionId) {
            // Camera & View Controls
            case 'recenter-view':
                this.recenterView();
                break;
            case 'reset-camera':
                this.resetCamera();
                break;
            case 'camera-presets':
                this.showCameraPresets();
                break;
                
            // Render Controls
            case 'stop-render':
                this.stopRender();
                break;
            case 'restart-render':
                this.restartRender();
                break;
            case 'pause-render':
                this.pauseRender();
                break;
            case 'start-render':
                this.startRender();
                break;
            case 'real-time-render':
                this.toggleRealTimeRender();
                break;
                
            // Picking Tools
            case 'focus-picker':
                this.togglePickingMode('focus');
                break;
            case 'white-balance-picker':
                this.togglePickingMode('whiteBalance');
                break;
            case 'material-picker':
                this.togglePickingMode('material');
                break;
            case 'object-picker':
                this.togglePickingMode('object');
                break;
            case 'camera-target-picker':
                this.togglePickingMode('cameraTarget');
                break;
                
            // Region Tools
            case 'render-region-picker':
                this.togglePickingMode('renderRegion');
                break;
            case 'film-region-picker':
                this.togglePickingMode('filmRegion');
                break;
                
            // Rendering Settings
            case 'clay-mode':
                this.toggleClayMode();
                break;
            case 'subsample-2x2':
                this.setSubSampling('2x2');
                break;
            case 'subsample-4x4':
                this.setSubSampling('4x4');
                break;
            case 'decal-wireframe':
                this.toggleDecalWireframe();
                break;
            case 'render-priority':
                this.showRenderPriorityMenu();
                break;
                
            // Output Controls
            case 'copy-clipboard':
                this.copyToClipboard();
                break;
            case 'save-render':
                this.saveRender();
                break;
            case 'export-passes':
                this.exportRenderPasses();
                break;
            case 'background-image':
                this.setBackgroundImage();
                break;
                
            // Viewport Controls
            case 'viewport-resolution-lock':
                this.toggleViewportResolutionLock();
                break;
            case 'lock-viewport':
                this.toggleViewportLock();
                break;
                
            // Object Manipulation
            case 'object-control-alignment':
                this.toggleObjectControlAlignment();
                break;
            case 'translate-gizmo':
                this.setActiveGizmo('translate');
                break;
            case 'rotate-gizmo':
                this.setActiveGizmo('rotate');
                break;
            case 'scale-gizmo':
                this.setActiveGizmo('scale');
                break;
            case 'world-coordinate':
                this.toggleWorldCoordinate();
                break;
                
            default:
                console.log(`⚠️ Action ${actionId} not yet implemented`);
        }
        
        // Refresh toolbar to update active states
        this.refreshToolbar();
    }
    
    // ========================================
    // CAMERA & VIEW CONTROLS
    // ========================================
    
    recenterView() {
        console.log('📐 Recentering view...');
        // TODO: makeGrpcCall('RecenterView', {})
        // Centers the render view display area without affecting zoom level
    }
    
    async resetCamera() {
        console.log('📷 Resetting camera...');
        
        // Reset camera to default position and target
        // Using the same camera API that's already working in the system
        const defaultPosition = { x: 1.14, y: 11.99, z: 20.61 };
        const defaultTarget = { x: 0, y: 0, z: 0 };
        const defaultFov = 45;
        
        if (this.client && this.client.setCameraPositionAndTarget) {
            try {
                await this.client.setCameraPositionAndTarget(
                    defaultPosition.x, defaultPosition.y, defaultPosition.z,
                    defaultTarget.x, defaultTarget.y, defaultTarget.z
                );
                console.log('✅ Camera reset to default position successfully');
            } catch (error) {
                console.error('❌ Failed to reset camera:', error);
            }
        } else {
            console.warn('⚠️ Camera reset not available - no client or method');
        }
    }
    
    showCameraPresets() {
        console.log('🎯 Showing camera presets...');
        // TODO: makeGrpcCall('GetCameraPresets', {})
        // Show camera preset menu/dialog
    }
    
    // ========================================
    // RENDER CONTROLS
    // ========================================
    
    async stopRender() {
        console.log('⏹️ Stopping render...');
        
        // Make real gRPC call to stop rendering
        const result = await this.makeGrpcCall('ApiRenderEngine', 'stopRendering');
        
        if (result && result.success !== false) {
            this.updateRenderStatus('stopped');
            console.log('✅ Render stopped successfully');
        } else {
            console.error('❌ Failed to stop render');
            // Still update UI to show stopped state for user feedback
            this.updateRenderStatus('stopped');
        }
    }
    
    async restartRender() {
        console.log('🔄 Restarting render...');
        
        // Make real gRPC call to restart rendering
        const result = await this.makeGrpcCall('ApiRenderEngine', 'restartRendering');
        
        if (result && result.success !== false) {
            this.updateRenderStatus('rendering');
            console.log('✅ Render restarted successfully');
        } else {
            console.error('❌ Failed to restart render');
            // Still update UI to show rendering state for user feedback
            this.updateRenderStatus('rendering');
        }
    }
    
    async pauseRender() {
        console.log('⏸️ Pausing render...');
        
        // Make real gRPC call to pause rendering
        const result = await this.makeGrpcCall('ApiRenderEngine', 'pauseRendering');
        
        if (result && result.success !== false) {
            this.updateRenderStatus('paused');
            console.log('✅ Render paused successfully');
        } else {
            console.error('❌ Failed to pause render');
            // Still update UI to show paused state for user feedback
            this.updateRenderStatus('paused');
        }
    }
    
    async startRender() {
        console.log('▶️ Starting/resuming render...');
        
        // Make real gRPC call to continue rendering (resume from pause)
        const result = await this.makeGrpcCall('ApiRenderEngine', 'continueRendering');
        
        if (result && result.success !== false) {
            this.updateRenderStatus('rendering');
            console.log('✅ Render started/resumed successfully');
        } else {
            console.error('❌ Failed to start/resume render');
            // Still update UI to show rendering state for user feedback
            this.updateRenderStatus('rendering');
        }
    }
    
    async toggleRealTimeRender() {
        this.realTimeMode = !this.realTimeMode;
        console.log(`⚡ Real-time rendering: ${this.realTimeMode ? 'ON' : 'OFF'}`);
        
        // Real-time mode typically involves setting render priority and continuous rendering
        // For now, we'll use render priority as a proxy for real-time mode
        const priority = this.realTimeMode ? 'high' : 'normal';
        
        const result = await this.makeGrpcCall('ApiRenderEngine', 'setRenderPriority', {
            priority: priority
        });
        
        if (result && result.success !== false) {
            console.log(`✅ Real-time mode ${this.realTimeMode ? 'enabled' : 'disabled'} successfully`);
            this.renderPriority = priority;
        } else {
            console.error(`❌ Failed to ${this.realTimeMode ? 'enable' : 'disable'} real-time mode`);
            // Revert the state if the call failed
            this.realTimeMode = !this.realTimeMode;
        }
        
        // Update button visual state
        this.updateButtonState('real-time-render', this.realTimeMode);
    }
    
    // ========================================
    // PICKING TOOLS
    // ========================================
    
    togglePickingMode(mode) {
        if (this.currentPickingMode === mode) {
            this.currentPickingMode = 'none';
            console.log(`🎯 Disabled ${mode} picker`);
        } else {
            this.currentPickingMode = mode;
            console.log(`🎯 Enabled ${mode} picker`);
        }
        
        switch (mode) {
            case 'focus':
                // TODO: makeGrpcCall('SetFocusPickerMode', { enabled: this.currentPickingMode === 'focus' })
                break;
            case 'whiteBalance':
                // TODO: makeGrpcCall('SetWhiteBalancePickerMode', { enabled: this.currentPickingMode === 'whiteBalance' })
                break;
            case 'material':
                // TODO: makeGrpcCall('SetMaterialPickerMode', { enabled: this.currentPickingMode === 'material' })
                break;
            case 'object':
                // TODO: makeGrpcCall('SetObjectPickerMode', { enabled: this.currentPickingMode === 'object' })
                break;
            case 'cameraTarget':
                // TODO: makeGrpcCall('SetCameraTargetPickerMode', { enabled: this.currentPickingMode === 'cameraTarget' })
                break;
            case 'renderRegion':
                // TODO: makeGrpcCall('SetRenderRegionPickerMode', { enabled: this.currentPickingMode === 'renderRegion' })
                break;
            case 'filmRegion':
                // TODO: makeGrpcCall('SetFilmRegionPickerMode', { enabled: this.currentPickingMode === 'filmRegion' })
                break;
        }
    }
    
    // ========================================
    // RENDERING SETTINGS
    // ========================================
    
    toggleClayMode() {
        this.clayMode = !this.clayMode;
        console.log(`🏺 Clay mode: ${this.clayMode ? 'ON' : 'OFF'}`);
        // TODO: makeGrpcCall('SetClayMode', { enabled: this.clayMode })
        // Shows model details without complex texturing
    }
    
    setSubSampling(mode) {
        if (this.subSampling === mode) {
            this.subSampling = 'none';
        } else {
            this.subSampling = mode;
        }
        console.log(`🔲 Sub-sampling: ${this.subSampling}`);
        // TODO: makeGrpcCall('SetSubSamplingMode', { mode: this.subSampling })
        // Reduces render resolution for smoother navigation
    }
    
    toggleDecalWireframe() {
        this.decalWireframe = !this.decalWireframe;
        console.log(`🔲 Decal wireframe: ${this.decalWireframe ? 'ON' : 'OFF'}`);
        // TODO: makeGrpcCall('SetDecalWireframe', { enabled: this.decalWireframe })
        // Toggles wireframe along decal boundaries
    }
    
    showRenderPriorityMenu() {
        console.log('⚙️ Showing render priority menu...');
        // TODO: Show priority menu (low, normal, high)
        // TODO: makeGrpcCall('SetRenderPriority', { priority: selectedPriority })
    }
    
    // ========================================
    // OUTPUT CONTROLS
    // ========================================
    
    copyToClipboard() {
        console.log('📋 Copying render to clipboard...');
        // TODO: makeGrpcCall('CopyRenderToClipboard', {})
        // Copies current render to clipboard in LDR format
    }
    
    saveRender() {
        console.log('💾 Saving render...');
        // TODO: Show save dialog and makeGrpcCall('SaveRender', { filename, format })
        // Saves current render to disk in specific format
    }
    
    exportRenderPasses() {
        console.log('📤 Exporting render passes...');
        // TODO: makeGrpcCall('ShowExportPassesDialog', {})
        // Brings up Render Passes Export window
    }
    
    setBackgroundImage() {
        console.log('🖼️ Setting background image...');
        // TODO: Show file dialog and makeGrpcCall('SetBackgroundImage', { imagePath })
        // Places background image in Render Viewport
    }
    
    // ========================================
    // VIEWPORT CONTROLS
    // ========================================
    
    toggleViewportResolutionLock() {
        this.viewportResolutionLock = !this.viewportResolutionLock;
        console.log(`🔒 Viewport resolution lock: ${this.viewportResolutionLock ? 'ON' : 'OFF'}`);
        // TODO: makeGrpcCall('SetViewportResolutionLock', { enabled: this.viewportResolutionLock })
        // Adjusts render resolution to viewport size
    }
    
    toggleViewportLock() {
        this.viewportLocked = !this.viewportLocked;
        console.log(`🔐 Viewport lock: ${this.viewportLocked ? 'ON' : 'OFF'}`);
        // TODO: makeGrpcCall('SetViewportLock', { enabled: this.viewportLocked })
        // Prevents accidental changes or render restarts
    }
    
    // ========================================
    // OBJECT MANIPULATION
    // ========================================
    
    toggleObjectControlAlignment() {
        this.objectControlMode = this.objectControlMode === 'world' ? 'local' : 'world';
        console.log(`🌐 Object control alignment: ${this.objectControlMode}`);
        // TODO: makeGrpcCall('SetObjectControlAlignment', { mode: this.objectControlMode })
        // Specifies coordinate system for object manipulation
    }
    
    setActiveGizmo(gizmo) {
        if (this.activeGizmo === gizmo) {
            this.activeGizmo = 'none';
        } else {
            this.activeGizmo = gizmo;
        }
        console.log(`🎛️ Active gizmo: ${this.activeGizmo}`);
        
        switch (gizmo) {
            case 'translate':
                // TODO: makeGrpcCall('SetTranslateGizmo', { enabled: this.activeGizmo === 'translate' })
                break;
            case 'rotate':
                // TODO: makeGrpcCall('SetRotateGizmo', { enabled: this.activeGizmo === 'rotate' })
                break;
            case 'scale':
                // TODO: makeGrpcCall('SetScaleGizmo', { enabled: this.activeGizmo === 'scale' })
                break;
        }
    }
    
    toggleWorldCoordinate() {
        this.worldCoordinateDisplay = !this.worldCoordinateDisplay;
        console.log(`🧭 World coordinate display: ${this.worldCoordinateDisplay ? 'ON' : 'OFF'}`);
        // TODO: makeGrpcCall('SetWorldCoordinateDisplay', { enabled: this.worldCoordinateDisplay })
        // Shows world coordinate axis in viewport corner
    }
    
    // ========================================
    // UPDATE METHODS
    // ========================================
    
    refreshToolbar() {
        // Re-render toolbar to update active states
        const toolbar = this.container.querySelector('.render-toolbar');
        if (toolbar) {
            toolbar.remove();
        }
        this.createRenderToolbar();
    }
    
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
        if (statusEl) {
            statusEl.textContent = `(${this.renderStats.status})`;
            statusEl.className = `render-status-${this.renderStats.status}`;
        }
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
    
    // ========================================
    // INTEGRATION METHODS FOR EXTERNAL UPDATES
    // ========================================
    
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
        console.error('🚨 Render error:', error);
    }
}

// Export for use in other modules
if (typeof module !== 'undefined' && module.exports) {
    module.exports = RenderToolbar;
}