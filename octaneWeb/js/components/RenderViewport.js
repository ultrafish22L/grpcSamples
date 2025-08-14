/**
 * Render Viewport Component
 * 2D image display area with mouse-controlled camera sync to live Octane
 * Replaces WebGL viewport with simple image display for future render output
 */

class RenderViewport extends OctaneComponent {
    constructor(element, client, stateManager) {
        super(element, client, stateManager);
        
        // 2D viewport elements
        this.viewport = null;
        this.imageDisplay = null;
        this.statusOverlay = null;
        
        // Camera system for LiveLink sync
        this.camera = {
            radius: 20.0,      // Distance from target
            theta: 0.0,        // Horizontal rotation (radians)
            phi: 0.0,          // Vertical rotation (radians)
            center: [0.0, 0.0, 0.0],  // Look-at target
            fov: 45.0,         // Field of view
            sensitivity: 0.01,  // Mouse sensitivity
            zoomSpeed: 0.1     // Wheel zoom speed
        };
        
        // Mouse interaction state
        this.mouse = {
            dragging: false,
            panning: false,
            lastX: 0,
            lastY: 0
        };
        
        // LiveLink sync state
        this.syncEnabled = true;
        this.lastSyncTime = 0;
        this.syncThrottle = 100; // Minimum ms between sync calls - reduced for more responsive camera
        this.syncCount = 0;
        
        // Background image polling state
        this.imagePolling = false;
        this.imagePollTimeout = null;
        this.imagePollInterval = 200; // Poll every 200ms for responsive image updates
        
        console.log('📷 Camera initialized for LiveLink sync:', {
            radius: this.camera.radius,
            theta: this.camera.theta,
            phi: this.camera.phi,
            center: this.camera.center,
            fov: this.camera.fov
        });
    }
    
    async onInitialize() {
        console.log('🎯 Initializing 2D Render Viewport with LiveLink camera sync...');
        
        try {
            // Create 2D viewport container
            await this.create2DViewport();
            
            // Get initial camera state from Octane
            await this.syncFromOctane();
            
            // Setup mouse event handlers
            this.setupEventHandlers();
            
            // Start background image polling
            this.startImagePolling();
            
            console.log('✅ RenderViewport initialized successfully');
            
        } catch (error) {
            console.error('❌ Failed to initialize RenderViewport:', error);
            this.showError('Failed to initialize render viewport', error.message);
        }
    }
    
    /**
     * Create 2D viewport for image display and mouse interaction
     */
    async create2DViewport() {
        // Remove any existing content
        this.element.innerHTML = '';
        
        // Create main viewport container
        this.viewport = document.createElement('div');
        this.viewport.className = 'render-viewport-2d';
        this.viewport.style.cssText = `
            width: 100%;
            height: 100%;
            position: relative;
            background: #1a1a1a;
            border: 1px solid #333;
            cursor: grab;
            overflow: hidden;
            display: flex;
            align-items: center;
            justify-content: center;
        `;
        
        // Create image display area
        this.imageDisplay = document.createElement('div');
        this.imageDisplay.className = 'image-display';
        this.imageDisplay.style.cssText = `
            width: 100%;
            height: 100%;
            background: #2a2a2a;
            display: flex;
            align-items: center;
            justify-content: center;
            flex-direction: column;
            color: #888;
            font-family: 'Segoe UI', sans-serif;
        `;
        
        // Create placeholder content
        const icon = document.createElement('div');
        icon.style.cssText = `
            font-size: 48px;
            margin-bottom: 16px;
            opacity: 0.6;
        `;
        icon.textContent = '🖼️';
        
        const title = document.createElement('div');
        title.style.cssText = `
            font-size: 16px;
            font-weight: 500;
            margin-bottom: 8px;
            color: #aaa;
        `;
        title.textContent = 'Render Viewport';
        
        const subtitle = document.createElement('div');
        subtitle.style.cssText = `
            font-size: 12px;
            opacity: 0.7;
            text-align: center;
            line-height: 1.4;
        `;
        subtitle.innerHTML = 'Mouse drag to orbit camera<br>Mouse wheel to zoom<br>Automatic render polling active';
        
        this.imageDisplay.appendChild(icon);
        this.imageDisplay.appendChild(title);
        this.imageDisplay.appendChild(subtitle);
        
        // Create status overlay
        this.statusOverlay = document.createElement('div');
        this.statusOverlay.className = 'viewport-status';
        this.statusOverlay.style.cssText = `
            position: absolute;
            top: 8px;
            left: 8px;
            background: rgba(0, 0, 0, 0.7);
            color: #fff;
            padding: 4px 8px;
            border-radius: 4px;
            font-size: 11px;
            font-family: monospace;
            pointer-events: none;
        `;
        this.statusOverlay.textContent = 'Polling: Active';
        
        // Assemble viewport
        this.viewport.appendChild(this.imageDisplay);
        this.viewport.appendChild(this.statusOverlay);
        this.element.appendChild(this.viewport);
        
        console.log('✅ 2D viewport created');
    }
    
    /**
     * Setup event handlers for mouse interaction
     */
    setupEventHandlers() {
        // Mouse events on viewport
        this.viewport.addEventListener('mousedown', (e) => this.handleMouseDown(e));
        this.viewport.addEventListener('mousemove', (e) => this.handleMouseMove(e));
        this.viewport.addEventListener('mouseup', (e) => this.handleMouseUp(e));
        this.viewport.addEventListener('wheel', (e) => this.handleWheel(e));
        this.viewport.addEventListener('contextmenu', (e) => e.preventDefault());
        
        // Prevent text selection during drag
        this.viewport.addEventListener('selectstart', (e) => e.preventDefault());
        
        // Window resize handler for responsive viewport
        this.resizeHandler = () => this.handleResize();
        window.addEventListener('resize', this.resizeHandler);
        
        // Initial resize to set proper dimensions
        this.handleResize();
        
        console.log('✅ Event handlers setup complete');
    }
    
    /**
     * Handle mouse down events
     */
    handleMouseDown(event) {
        this.mouse.dragging = event.button === 0; // Left button
        this.mouse.panning = event.button === 2;  // Right button
        this.mouse.lastX = event.clientX;
        this.mouse.lastY = event.clientY;
        
        if (this.mouse.dragging || this.mouse.panning) {
            this.viewport.style.cursor = this.mouse.panning ? 'move' : 'grabbing';
            this.updateStatus('Dragging camera...');
        }
        
        console.log('🖱️ Mouse down:', {
            button: event.button,
            dragging: this.mouse.dragging,
            panning: this.mouse.panning
        });
    }
    
    /**
     * Handle mouse move events
     */
    handleMouseMove(event) {
        if (this.mouse.dragging || this.mouse.panning) {
            const deltaX = event.clientX - this.mouse.lastX;
            const deltaY = event.clientY - this.mouse.lastY;
            
            if (this.mouse.dragging) {
                // Orbit camera
                this.camera.theta += deltaX * this.camera.sensitivity;
                this.camera.phi = Math.max(-Math.PI/2 + 0.1, 
                                         Math.min(Math.PI/2 - 0.1, 
                                                this.camera.phi + deltaY * this.camera.sensitivity));
                
                // Sync to Octane
                this.syncToOctane();
            } else if (this.mouse.panning) {
                // Pan camera (move center point)
                // TODO: Implement panning if needed
            }
            
            this.mouse.lastX = event.clientX;
            this.mouse.lastY = event.clientY;
        }
    }
    
    /**
     * Handle mouse up events
     */
    handleMouseUp(event) {
        this.mouse.dragging = false;
        this.mouse.panning = false;
        this.viewport.style.cursor = 'grab';
        this.updateStatus('LiveLink: Ready');
    }
    
    /**
     * Handle mouse wheel events
     */
    handleWheel(event) {
        event.preventDefault();
        
        // Zoom camera
        const zoomDelta = event.deltaY * this.camera.zoomSpeed;
        this.camera.radius = Math.max(1.0, Math.min(100.0, this.camera.radius + zoomDelta));
        
        this.updateStatus(`Zoom: ${this.camera.radius.toFixed(1)}`);
        
        // Sync to Octane
        this.syncToOctane();
        
        console.log('🔍 Wheel zoom:', {
            deltaY: event.deltaY,
            newRadius: this.camera.radius
        });
    }
    
    /**
     * Calculate camera position from spherical coordinates
     */
    getCameraPosition() {
        const x = this.camera.center[0] + this.camera.radius * Math.sin(this.camera.theta) * Math.cos(this.camera.phi);
        const y = this.camera.center[1] + this.camera.radius * Math.sin(this.camera.phi);
        const z = this.camera.center[2] + this.camera.radius * Math.cos(this.camera.theta) * Math.cos(this.camera.phi);
        return [x, y, z];
    }
    
    /**
     * Sync camera state to Octane
     */
    async syncToOctane() {
        if (!this.syncEnabled || !this.client) return;
        
        // Throttle sync calls
        const now = Date.now();
        if (now - this.lastSyncTime < this.syncThrottle) return;
        this.lastSyncTime = now;
        
        try {
            const position = this.getCameraPosition();
            const cameraState = {
                position: { x: position[0], y: position[1], z: position[2] },
                target: { x: this.camera.center[0], y: this.camera.center[1], z: this.camera.center[2] },
                up: { x: 0, y: 1, z: 0 },
                fov: this.camera.fov
            };
            
            await this.client.setCamera(cameraState);
            this.syncCount++;
            
            console.log('📤 Camera synced to Octane:', {
                position: `(${position[0].toFixed(2)}, ${position[1].toFixed(2)}, ${position[2].toFixed(2)})`,
                radius: this.camera.radius.toFixed(2),
                theta: (this.camera.theta * 180 / Math.PI).toFixed(1) + '°',
                phi: (this.camera.phi * 180 / Math.PI).toFixed(1) + '°',
                syncCount: this.syncCount
            });
            
        } catch (error) {
            console.error('❌ Failed to sync camera to Octane:', error);
            this.updateStatus('Sync error');
        }
    }
    
    /**
     * Sync camera state from Octane
     */
    async syncFromOctane() {
        if (!this.client) return;
        
        try {
            const cameraData = await this.client.getCamera();
            if (cameraData && cameraData.position && cameraData.target) {
                // Convert Octane camera to spherical coordinates
                const pos = cameraData.position;
                const target = cameraData.target;
                
                this.camera.center = [target.x, target.y, target.z];
                
                const direction = [
                    pos.x - target.x,
                    pos.y - target.y,
                    pos.z - target.z
                ];
                
                this.camera.radius = Math.sqrt(direction[0] * direction[0] + 
                                             direction[1] * direction[1] + 
                                             direction[2] * direction[2]);
                
                this.camera.theta = Math.atan2(direction[0], direction[2]);
                this.camera.phi = Math.asin(direction[1] / this.camera.radius);
                
                if (cameraData.fov) {
                    this.camera.fov = cameraData.fov;
                }
                
                console.log('📥 Camera synced from Octane:', {
                    position: `(${pos.x.toFixed(2)}, ${pos.y.toFixed(2)}, ${pos.z.toFixed(2)})`,
                    target: `(${target.x.toFixed(2)}, ${target.y.toFixed(2)}, ${target.z.toFixed(2)})`,
                    radius: this.camera.radius.toFixed(2),
                    fov: this.camera.fov.toFixed(1) + '°'
                });
                
                this.updateStatus('Synced from Octane');
            }
            
        } catch (error) {
            console.error('❌ Failed to sync camera from Octane:', error);
            this.updateStatus('Sync error');
        }
    }
    
    /**
     * Update status overlay
     */
    updateStatus(message) {
        if (this.statusOverlay) {
            this.statusOverlay.textContent = message;
            
            // Auto-reset to ready after 2 seconds
            setTimeout(() => {
                if (this.statusOverlay) {
                    this.statusOverlay.textContent = 'LiveLink: Ready';
                }
            }, 2000);
        }
    }
    
    /**
     * Show error message
     */
    showError(title, message) {
        console.error(`❌ ${title}: ${message}`);
        this.updateStatus('Error: ' + title);
        
        // Update viewport to show error
        if (this.imageDisplay) {
            this.imageDisplay.innerHTML = `
                <div style="color: #ff6b6b; font-size: 24px; margin-bottom: 16px;">⚠️</div>
                <div style="color: #ff6b6b; font-weight: 500; margin-bottom: 8px;">${title}</div>
                <div style="color: #ccc; font-size: 12px; text-align: center;">${message}</div>
            `;
        }
    }
    
    /**
     * Enable/disable camera sync
     */
    setSyncEnabled(enabled) {
        this.syncEnabled = enabled;
        this.updateStatus(enabled ? 'LiveLink: Enabled' : 'LiveLink: Disabled');
        console.log(`📡 Camera sync ${enabled ? 'enabled' : 'disabled'}`);
    }
    
    /**
     * Get current camera stats for debugging
     */
    getCameraStats() {
        const position = this.getCameraPosition();
        return {
            position: position,
            target: this.camera.center,
            radius: this.camera.radius,
            theta: this.camera.theta * 180 / Math.PI,
            phi: this.camera.phi * 180 / Math.PI,
            fov: this.camera.fov,
            syncCount: this.syncCount,
            syncEnabled: this.syncEnabled
        };
    }

    /**
     * Start background polling for render images
     */
    startImagePolling() {
        if (this.imagePolling) {
            return; // Already polling
        }
        
        console.log('🔄 Starting background image polling...');
        this.imagePolling = true;
        this.pollForImages();
    }
    
    /**
     * Stop background polling for render images
     */
    stopImagePolling() {
        console.log('⏹️ Stopping background image polling...');
        this.imagePolling = false;
        
        if (this.imagePollTimeout) {
            clearTimeout(this.imagePollTimeout);
            this.imagePollTimeout = null;
        }
    }
    
    /**
     * Poll for render images in background
     */
    async pollForImages() {
        if (!this.imagePolling || !this.client) {
            return;
        }
        
        try {
            // Simply grab render result - ignore empty responses
            const result = await this.client.makeGrpcCall('ApiRenderEngineService', 'grabRenderResult', {});
            
            if (result && result.success && result.data && result.data.renderImages) {
                const renderImages = result.data.renderImages;
                
                // Check if we have actual image data
                if (renderImages.data && renderImages.data.length > 0) {
                    console.log('📸 New render image received from background polling');
                    this.displayRenderImage(result.data);
                    this.updateStatus('New image received');
                }
                // Ignore empty responses - this is normal
            }
            
        } catch (error) {
            // Ignore connection errors during polling - don't spam console
            if (!error.message.includes('Connection') && !error.message.includes('Network')) {
                console.warn('⚠️ Image polling error (continuing):', error.message);
            }
        }
        
        // Schedule next poll
        if (this.imagePolling) {
            this.imagePollTimeout = setTimeout(() => {
                this.pollForImages();
            }, this.imagePollInterval);
        }
    }

    /**
     * Display rendered image in the viewport
     */
    displayRenderImage(imageData) {
        try {
            // Clear existing content
            this.imageDisplay.innerHTML = '';
            
            console.log('🔍 Processing image data structure:', imageData);
            
            // Handle Octane render result format
            if (imageData.renderImages && imageData.renderImages.data && imageData.renderImages.data.length > 0) {
                // Get first render image from array
                const renderImage = imageData.renderImages.data[0];
                console.log('📸 Found render image:', renderImage);
                
                if (renderImage.buffer && renderImage.buffer.data && renderImage.size) {
                    this.displayRawImageBuffer(renderImage);
                    return;
                }
            }
            
            // Handle direct renderImages.data format (single image)
            if (imageData.renderImages && imageData.renderImages.data && imageData.renderImages.data.buffer) {
                console.log('📸 Found direct render image:', imageData.renderImages.data);
                const renderImage = imageData.renderImages.data;
                
                if (renderImage.buffer && renderImage.buffer.data && renderImage.size) {
                    this.displayRawImageBuffer(renderImage);
                    return;
                }
            }
            
            // Create image element for other formats
            const img = document.createElement('img');
            img.style.cssText = `
                max-width: 100%;
                max-height: 100%;
                object-fit: contain;
                border-radius: 4px;
            `;
            
            // Handle different image data formats
            if (imageData.buffer && imageData.buffer.data) {
                // Handle binary buffer data
                const uint8Array = new Uint8Array(imageData.buffer.data);
                const blob = new Blob([uint8Array], { type: 'image/png' });
                img.src = URL.createObjectURL(blob);
            } else if (typeof imageData === 'string') {
                // Handle base64 encoded data
                if (imageData.startsWith('data:image/')) {
                    img.src = imageData;
                } else {
                    img.src = `data:image/png;base64,${imageData}`;
                }
            } else if (imageData.url) {
                // Handle URL reference
                img.src = imageData.url;
            } else {
                console.log('🔍 Unknown image data format:', imageData);
                this.showImageError('Unknown image format');
                return;
            }
            
            // Add load handlers
            img.onload = () => {
                console.log('✅ Render image loaded successfully');
                this.updateStatus('Image loaded');
            };
            
            img.onerror = (error) => {
                console.error('❌ Failed to load render image:', error);
                this.showImageError('Failed to load image');
            };
            
            this.imageDisplay.appendChild(img);
            
        } catch (error) {
            console.error('❌ Failed to display render image:', error);
            this.showImageError('Failed to display image', error.message);
        }
    }

    /**
     * Display raw image buffer from Octane render result
     */
    displayRawImageBuffer(renderImage) {
        try {
            const { buffer, size, pitch } = renderImage;
            const width = size.x;
            const height = size.y;
            
            console.log(`🖼️ Processing raw image buffer: ${width}x${height}, pitch: ${pitch}`);
            
            // Create canvas to convert raw buffer to displayable image
            const canvas = document.createElement('canvas');
            canvas.width = width;
            canvas.height = height;
            canvas.style.cssText = `
                max-width: 100%;
                max-height: 100%;
                object-fit: contain;
                border-radius: 4px;
            `;
            
            const ctx = canvas.getContext('2d');
            const imageData = ctx.createImageData(width, height);
            
            // Convert buffer data to Uint8Array
            const bufferData = new Uint8Array(buffer.data);
            console.log(`📊 Buffer size: ${bufferData.length} bytes`);
            
            // Copy RGBA data to canvas ImageData
            // Octane format appears to be RGBA with 4 bytes per pixel
            for (let y = 0; y < height; y++) {
                for (let x = 0; x < width; x++) {
                    const srcIndex = y * pitch + x * 4; // 4 bytes per pixel (RGBA)
                    const dstIndex = (y * width + x) * 4;
                    
                    if (srcIndex + 3 < bufferData.length) {
                        imageData.data[dstIndex] = bufferData[srcIndex];     // R
                        imageData.data[dstIndex + 1] = bufferData[srcIndex + 1]; // G
                        imageData.data[dstIndex + 2] = bufferData[srcIndex + 2]; // B
                        imageData.data[dstIndex + 3] = bufferData[srcIndex + 3]; // A
                    }
                }
            }
            
            // Draw to canvas
            ctx.putImageData(imageData, 0, 0);
            
            // Add to viewport
            this.imageDisplay.appendChild(canvas);
            
            // Update status with render info
            const samples = renderImage.tonemappedSamplesPerPixel || renderImage.calculatedSamplesPerPixel || 0;
            const renderTime = renderImage.renderTime || 0;
            this.updateStatus(`Image: ${width}x${height}, ${samples} samples, ${renderTime.toFixed(2)}s`);
            
            console.log('✅ Raw image buffer displayed successfully');
            
        } catch (error) {
            console.error('❌ Failed to display raw image buffer:', error);
            this.showImageError('Failed to process raw image', error.message);
        }
    }

    /**
     * Show image error message
     */
    showImageError(message, details = '') {
        this.imageDisplay.innerHTML = '';
        
        const errorDiv = document.createElement('div');
        errorDiv.style.cssText = `
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            color: #ff6b6b;
            font-family: 'Segoe UI', sans-serif;
            text-align: center;
        `;
        
        const icon = document.createElement('div');
        icon.style.cssText = `
            font-size: 48px;
            margin-bottom: 16px;
            opacity: 0.6;
        `;
        icon.textContent = '❌';
        
        const title = document.createElement('div');
        title.style.cssText = `
            font-size: 16px;
            font-weight: 500;
            margin-bottom: 8px;
        `;
        title.textContent = message;
        
        if (details) {
            const subtitle = document.createElement('div');
            subtitle.style.cssText = `
                font-size: 12px;
                opacity: 0.7;
                max-width: 300px;
                word-wrap: break-word;
            `;
            subtitle.textContent = details;
            errorDiv.appendChild(subtitle);
        }
        
        errorDiv.appendChild(icon);
        errorDiv.appendChild(title);
        this.imageDisplay.appendChild(errorDiv);
    }

    /**
     * Handle window resize to make viewport responsive
     */
    handleResize() {
        if (!this.viewport || !this.element) return;
        
        // Get the container dimensions
        const containerRect = this.element.getBoundingClientRect();
        
        // Update viewport dimensions to fill available space
        this.viewport.style.width = '100%';
        this.viewport.style.height = '100%';
        
        console.log('📐 Viewport resized:', {
            width: containerRect.width,
            height: containerRect.height
        });
    }

    /**
     * Cleanup when component is destroyed
     */
    destroy() {
        this.stopImagePolling();
        
        // Remove resize handler
        if (this.resizeHandler) {
            window.removeEventListener('resize', this.resizeHandler);
            this.resizeHandler = null;
        }
        
        console.log('🧹 RenderViewport destroyed');
    }
}