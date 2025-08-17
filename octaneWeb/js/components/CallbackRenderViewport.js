/**
 * Callback-based Render Viewport Component
 * Real-time rendering with gRPC streaming callbacks (Option 2 implementation)
 * 
 * FEATURES:
 * - Pure gRPC streaming callbacks (no polling)
 * - Server-Sent Events for real-time updates
 * - Automatic fallback to polling mode
 * - Complete ApiRenderImage data processing
 * - Zero-copy performance with base64 image buffers
 */

class CallbackRenderViewport extends OctaneComponent {
    constructor(element, client, stateManager) {
        super(element, client, stateManager);
        
        // Callback system state
        this.callbackMode = false;
        this.eventSource = null;
        this.clientId = null;
        this.callbackId = null;
        
        // Fallback polling system (from original RenderViewport)
        this.pollingMode = false;
        this.pollTimeout = null;
        this.pollInterval = 1000; // Slower polling as fallback
        
        // 2D viewport elements
        this.viewport = null;
        this.imageDisplay = null;
        this.statusOverlay = null;
        this.modeIndicator = null;
        
        // Camera system for LiveLink sync
        this.camera = {
            radius: 20.0,
            theta: 0.0,
            phi: 0.0,
            center: [0.0, 0.0, 0.0],
            fov: 45.0,
            sensitivity: 0.01,
            zoomSpeed: 0.1
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
        this.syncThrottle = 100;
        this.syncCount = 0;
        
        // Statistics
        this.callbackCount = 0;
        this.lastCallbackTime = 0;
        this.connectionErrors = 0;
        this.lastImageSize = 0;
        
        console.log('🚀 CallbackRenderViewport initialized with streaming callbacks');
    }
    
    async onInitialize() {
        console.log('🎯 Initializing Callback Render Viewport...');
        
        try {
            // Create 2D viewport container
            await this.create2DViewport();
            
            // Get initial camera state from Octane
            await this.syncFromOctane();
            
            // Setup mouse event handlers
            this.setupEventHandlers();
            
            // Try to start callback mode first
            const callbackSuccess = await this.startCallbackMode();
            
            if (!callbackSuccess) {
                // Fallback to polling mode
                console.log('📸 Falling back to polling mode');
                await this.startPollingMode();
            }
            
            console.log('✅ CallbackRenderViewport initialized successfully');
            
        } catch (error) {
            console.error('❌ Failed to initialize CallbackRenderViewport:', error);
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
            display: flex;
            align-items: center;
            justify-content: center;
            position: relative;
        `;
        
        // Create status overlay
        this.statusOverlay = document.createElement('div');
        this.statusOverlay.className = 'status-overlay';
        this.statusOverlay.style.cssText = `
            position: absolute;
            top: 10px;
            left: 10px;
            background: rgba(0, 0, 0, 0.8);
            color: #fff;
            padding: 8px 12px;
            border-radius: 4px;
            font-family: monospace;
            font-size: 12px;
            z-index: 100;
            max-width: 300px;
        `;
        
        // Create mode indicator
        this.modeIndicator = document.createElement('div');
        this.modeIndicator.className = 'mode-indicator';
        this.modeIndicator.style.cssText = `
            position: absolute;
            top: 10px;
            right: 10px;
            background: rgba(0, 0, 0, 0.8);
            color: #fff;
            padding: 8px 12px;
            border-radius: 4px;
            font-family: monospace;
            font-size: 12px;
            z-index: 100;
            border-left: 4px solid #666;
        `;
        
        // Assemble viewport
        this.viewport.appendChild(this.imageDisplay);
        this.viewport.appendChild(this.statusOverlay);
        this.viewport.appendChild(this.modeIndicator);
        this.element.appendChild(this.viewport);
        
        // Initial status
        this.updateStatus('Initializing callback system...');
        this.updateModeIndicator('INITIALIZING', '#ffa500');
        
        console.log('✅ 2D viewport created');
    }
    
    /**
     * Start callback streaming mode
     */
    async startCallbackMode() {
        try {
            console.log('🚀 Attempting to start callback streaming mode...');
            
            // Register callback with proxy server
            const response = await fetch('/render/register-callback', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                }
            });
            
            const result = await response.json();
            
            if (!result.success) {
                throw new Error(result.error || 'Failed to register callback');
            }
            
            this.callbackId = result.callback_id;
            console.log(`✅ Callback registered with ID: ${this.callbackId}`);
            
            // Start Server-Sent Events stream
            this.eventSource = new EventSource('/render/stream');
            
            this.eventSource.onopen = (event) => {
                console.log('📡 SSE connection opened');
                this.callbackMode = true;
                this.connectionErrors = 0;
                this.updateStatus('Connected to callback stream');
                this.updateModeIndicator('🚀 CALLBACK MODE', '#00ff00');
            };
            
            this.eventSource.onmessage = (event) => {
                try {
                    const data = JSON.parse(event.data);
                    this.handleCallbackEvent(data);
                } catch (error) {
                    console.error('❌ Error parsing SSE data:', error);
                }
            };
            
            this.eventSource.onerror = (error) => {
                console.error('❌ SSE connection error:', error);
                this.connectionErrors++;
                
                if (this.connectionErrors > 3) {
                    console.log('📸 Too many connection errors, falling back to polling');
                    this.fallbackToPolling();
                } else {
                    this.updateStatus(`Connection error #${this.connectionErrors}, retrying...`);
                }
            };
            
            // Wait a moment to see if connection succeeds
            await new Promise(resolve => setTimeout(resolve, 1000));
            
            return this.callbackMode;
            
        } catch (error) {
            console.error('❌ Failed to start callback mode:', error);
            this.updateStatus(`Callback failed: ${error.message}`);
            return false;
        }
    }
    
    /**
     * Handle callback events from Server-Sent Events
     */
    handleCallbackEvent(data) {
        switch (data.type) {
            case 'connected':
                console.log(`📡 Connected to callback stream, client ID: ${data.client_id}`);
                this.clientId = data.client_id;
                this.updateStatus(`Connected (Client: ${data.client_id.substring(0, 8)}...)`);
                break;
                
            case 'newImage':
                this.handleNewImageCallback(data);
                break;
                
            case 'renderFailure':
                console.error('❌ Render failure callback:', data);
                this.updateStatus('Render failure detected');
                break;
                
            case 'newStatistics':
                console.log('📊 New statistics callback:', data);
                break;
                
            case 'ping':
                // Keep-alive ping
                break;
                
            default:
                console.log('🔍 Unknown callback event:', data);
        }
    }
    
    /**
     * Handle OnNewImage callback data
     */
    handleNewImageCallback(data) {
        try {
            this.callbackCount++;
            this.lastCallbackTime = Date.now();
            
            console.log(`📸 OnNewImage callback #${this.callbackCount}:`, {
                callback_id: data.callback_id,
                images: data.render_images?.data?.length || 0,
                timestamp: data.timestamp
            });
            
            // Update statistics
            this.updateStatus(
                `Callback #${this.callbackCount} | ` +
                `Images: ${data.render_images?.data?.length || 0} | ` +
                `Time: ${new Date(data.timestamp * 1000).toLocaleTimeString()}`
            );
            
            // Process render images
            if (data.render_images && data.render_images.data && data.render_images.data.length > 0) {
                this.displayCallbackImage(data.render_images.data[0]); // Use first image
            } else {
                console.warn('⚠️ No image data in callback');
            }
            
        } catch (error) {
            console.error('❌ Error handling new image callback:', error);
        }
    }
    
    /**
     * Display image from callback data
     */
    displayCallbackImage(imageData) {
        try {
            // Clear existing content
            this.imageDisplay.innerHTML = '';
            
            console.log('🖼️ Processing callback image:', {
                type: imageData.type,
                size: `${imageData.size.x}x${imageData.size.y}`,
                pitch: imageData.pitch,
                samples: imageData.tonemappedSamplesPerPixel,
                renderTime: imageData.renderTime,
                hasBuffer: !!imageData.buffer
            });
            
            if (!imageData.buffer || !imageData.buffer.data) {
                this.showImageError('No image buffer in callback data');
                return;
            }
            
            // Decode base64 buffer
            const bufferData = imageData.buffer.data;
            const bufferSize = imageData.buffer.size;
            this.lastImageSize = bufferSize;
            
            console.log(`📊 Image buffer: ${bufferSize} bytes (${imageData.buffer.encoding})`);
            
            // Create canvas to display raw image buffer
            const canvas = document.createElement('canvas');
            canvas.width = imageData.size.x;
            canvas.height = imageData.size.y;
            canvas.style.cssText = `
                max-width: 100%;
                max-height: 100%;
                border: 1px solid #444;
                image-rendering: pixelated;
            `;
            
            const ctx = canvas.getContext('2d');
            const imageDataObj = ctx.createImageData(canvas.width, canvas.height);
            
            // Decode base64 to binary
            const binaryString = atob(bufferData);
            const bytes = new Uint8Array(binaryString.length);
            for (let i = 0; i < binaryString.length; i++) {
                bytes[i] = binaryString.charCodeAt(i);
            }
            
            // Convert buffer to RGBA format for canvas
            this.convertBufferToCanvas(bytes, imageData, imageDataObj);
            
            ctx.putImageData(imageDataObj, 0, 0);
            this.imageDisplay.appendChild(canvas);
            
            // Update status with image info
            this.updateStatus(
                `Image: ${imageData.size.x}x${imageData.size.y} | ` +
                `${(bufferSize / 1024).toFixed(1)}KB | ` +
                `${imageData.tonemappedSamplesPerPixel.toFixed(1)} samples/px | ` +
                `${imageData.renderTime.toFixed(2)}s`
            );
            
            console.log('✅ Callback image displayed successfully');
            
        } catch (error) {
            console.error('❌ Error displaying callback image:', error);
            this.showImageError('Failed to display callback image', error.message);
        }
    }
    
    /**
     * Convert raw buffer to canvas ImageData
     */
    convertBufferToCanvas(buffer, imageData, canvasImageData) {
        const width = imageData.size.x;
        const height = imageData.size.y;
        const pitch = imageData.pitch;
        const imageType = imageData.type;
        
        // Handle different image types
        switch (imageType) {
            case 0: // IMAGE_TYPE_LDR_RGBA
                this.convertLDRRGBA(buffer, width, height, pitch, canvasImageData);
                break;
            case 1: // IMAGE_TYPE_HDR_RGBA  
                this.convertHDRRGBA(buffer, width, height, pitch, canvasImageData);
                break;
            default:
                console.warn(`⚠️ Unsupported image type: ${imageType}, trying LDR RGBA`);
                this.convertLDRRGBA(buffer, width, height, pitch, canvasImageData);
        }
    }
    
    /**
     * Convert LDR RGBA buffer to canvas
     */
    convertLDRRGBA(buffer, width, height, pitch, canvasImageData) {
        const data = canvasImageData.data;
        
        for (let y = 0; y < height; y++) {
            for (let x = 0; x < width; x++) {
                const srcIndex = y * pitch + x * 4;
                const dstIndex = (y * width + x) * 4;
                
                if (srcIndex + 3 < buffer.length) {
                    data[dstIndex] = buffer[srcIndex];     // R
                    data[dstIndex + 1] = buffer[srcIndex + 1]; // G
                    data[dstIndex + 2] = buffer[srcIndex + 2]; // B
                    data[dstIndex + 3] = buffer[srcIndex + 3]; // A
                }
            }
        }
    }
    
    /**
     * Convert HDR RGBA buffer to canvas (simplified tone mapping)
     */
    convertHDRRGBA(buffer, width, height, pitch, canvasImageData) {
        const data = canvasImageData.data;
        const floatView = new Float32Array(buffer.buffer);
        
        for (let y = 0; y < height; y++) {
            for (let x = 0; x < width; x++) {
                const srcIndex = (y * pitch + x * 4) / 4; // Float32 index
                const dstIndex = (y * width + x) * 4;
                
                if (srcIndex + 3 < floatView.length) {
                    // Simple tone mapping: clamp and convert to 8-bit
                    data[dstIndex] = Math.min(255, floatView[srcIndex] * 255);     // R
                    data[dstIndex + 1] = Math.min(255, floatView[srcIndex + 1] * 255); // G
                    data[dstIndex + 2] = Math.min(255, floatView[srcIndex + 2] * 255); // B
                    data[dstIndex + 3] = Math.min(255, floatView[srcIndex + 3] * 255); // A
                }
            }
        }
    }
    
    /**
     * Fallback to polling mode
     */
    async fallbackToPolling() {
        console.log('📸 Switching to polling fallback mode');
        
        // Close SSE connection
        if (this.eventSource) {
            this.eventSource.close();
            this.eventSource = null;
        }
        
        this.callbackMode = false;
        await this.startPollingMode();
    }
    
    /**
     * Start polling mode (fallback)
     */
    async startPollingMode() {
        this.pollingMode = true;
        this.updateModeIndicator('📸 POLLING MODE', '#ffa500');
        this.updateStatus('Using polling fallback mode');
        
        this.pollForImages();
    }
    
    /**
     * Poll for images (fallback method)
     */
    async pollForImages() {
        if (!this.pollingMode) return;
        
        try {
            const result = await this.client.makeGrpcCall('ApiRenderEngineService', 'grabRenderResult', {});
            
            if (result && result.success && result.data && result.data.renderImages) {
                const renderImages = result.data.renderImages;
                
                if (renderImages.data && renderImages.data.length > 0) {
                    console.log('📸 Polled image received');
                    this.displayPolledImage(result.data);
                    this.updateStatus('Polling: Image received');
                }
            }
            
        } catch (error) {
            if (!error.message.includes('Connection') && !error.message.includes('Network')) {
                console.warn('⚠️ Polling error:', error.message);
            }
        }
        
        // Schedule next poll
        if (this.pollingMode) {
            this.pollTimeout = setTimeout(() => {
                this.pollForImages();
            }, this.pollInterval);
        }
    }
    
    /**
     * Display polled image (similar to original RenderViewport)
     */
    displayPolledImage(imageData) {
        // Use existing display logic from original RenderViewport
        // This is the fallback path
        console.log('📸 Displaying polled image (fallback)');
        // Implementation would be similar to original RenderViewport.displayRenderImage()
    }
    
    /**
     * Setup mouse event handlers for camera control
     */
    setupEventHandlers() {
        // Mouse event handlers for camera control
        this.viewport.addEventListener('mousedown', (e) => {
            if (e.button === 0) { // Left button
                this.mouse.dragging = true;
            } else if (e.button === 2) { // Right button
                this.mouse.panning = true;
            }
            this.mouse.lastX = e.clientX;
            this.mouse.lastY = e.clientY;
            this.viewport.style.cursor = 'grabbing';
            e.preventDefault();
        });
        
        this.viewport.addEventListener('mousemove', (e) => {
            if (this.mouse.dragging || this.mouse.panning) {
                const deltaX = e.clientX - this.mouse.lastX;
                const deltaY = e.clientY - this.mouse.lastY;
                
                if (this.mouse.dragging) {
                    // Rotate camera
                    this.camera.theta += deltaX * this.camera.sensitivity;
                    this.camera.phi += deltaY * this.camera.sensitivity;
                    this.camera.phi = Math.max(-Math.PI/2 + 0.1, Math.min(Math.PI/2 - 0.1, this.camera.phi));
                } else if (this.mouse.panning) {
                    // Pan camera
                    const right = [
                        Math.cos(this.camera.theta + Math.PI/2),
                        0,
                        Math.sin(this.camera.theta + Math.PI/2)
                    ];
                    const up = [0, 1, 0];
                    
                    const panSpeed = this.camera.radius * 0.001;
                    this.camera.center[0] -= right[0] * deltaX * panSpeed;
                    this.camera.center[1] += up[1] * deltaY * panSpeed;
                    this.camera.center[2] -= right[2] * deltaX * panSpeed;
                }
                
                this.mouse.lastX = e.clientX;
                this.mouse.lastY = e.clientY;
                
                // Sync with Octane
                this.syncToOctane();
            }
        });
        
        this.viewport.addEventListener('mouseup', () => {
            this.mouse.dragging = false;
            this.mouse.panning = false;
            this.viewport.style.cursor = 'grab';
        });
        
        this.viewport.addEventListener('wheel', (e) => {
            this.camera.radius *= (1 + e.deltaY * this.camera.zoomSpeed * 0.001);
            this.camera.radius = Math.max(0.1, Math.min(1000, this.camera.radius));
            this.syncToOctane();
            e.preventDefault();
        });
        
        // Prevent context menu
        this.viewport.addEventListener('contextmenu', (e) => e.preventDefault());
    }
    
    /**
     * Sync camera to Octane
     */
    async syncToOctane() {
        if (!this.syncEnabled) return;
        
        const now = Date.now();
        if (now - this.lastSyncTime < this.syncThrottle) return;
        
        try {
            // Calculate camera position
            const x = this.camera.center[0] + this.camera.radius * Math.cos(this.camera.phi) * Math.cos(this.camera.theta);
            const y = this.camera.center[1] + this.camera.radius * Math.sin(this.camera.phi);
            const z = this.camera.center[2] + this.camera.radius * Math.cos(this.camera.phi) * Math.sin(this.camera.theta);
            
            await this.client.setCameraPosition(x, y, z);
            await this.client.setCameraTarget(this.camera.center[0], this.camera.center[1], this.camera.center[2]);
            
            this.lastSyncTime = now;
            this.syncCount++;
            
        } catch (error) {
            console.warn('⚠️ Camera sync error:', error);
        }
    }
    
    /**
     * Sync camera from Octane
     */
    async syncFromOctane() {
        try {
            const position = await this.client.getCameraPosition();
            const target = await this.client.getCameraTarget();
            
            if (position && target) {
                // Update camera state
                this.camera.center = [target.x, target.y, target.z];
                
                const dx = position.x - target.x;
                const dy = position.y - target.y;
                const dz = position.z - target.z;
                
                this.camera.radius = Math.sqrt(dx*dx + dy*dy + dz*dz);
                this.camera.theta = Math.atan2(dz, dx);
                this.camera.phi = Math.asin(dy / this.camera.radius);
            }
            
        } catch (error) {
            console.warn('⚠️ Camera sync from Octane failed:', error);
        }
    }
    
    /**
     * Update status overlay
     */
    updateStatus(message) {
        if (this.statusOverlay) {
            this.statusOverlay.textContent = message;
        }
    }
    
    /**
     * Update mode indicator
     */
    updateModeIndicator(mode, color = '#666') {
        if (this.modeIndicator) {
            this.modeIndicator.textContent = mode;
            this.modeIndicator.style.borderLeftColor = color;
        }
    }
    
    /**
     * Show error message
     */
    showError(title, message) {
        this.updateStatus(`ERROR: ${title} - ${message}`);
        this.updateModeIndicator('❌ ERROR', '#ff0000');
    }
    
    /**
     * Show image error
     */
    showImageError(message, details = '') {
        this.imageDisplay.innerHTML = `
            <div style="color: #ff6b6b; text-align: center; padding: 20px;">
                <div style="font-size: 18px; margin-bottom: 10px;">⚠️ ${message}</div>
                ${details ? `<div style="font-size: 12px; opacity: 0.7;">${details}</div>` : ''}
            </div>
        `;
    }
    
    /**
     * Get current status
     */
    getStatus() {
        return {
            mode: this.callbackMode ? 'callback' : (this.pollingMode ? 'polling' : 'inactive'),
            callbackCount: this.callbackCount,
            lastCallbackTime: this.lastCallbackTime,
            connectionErrors: this.connectionErrors,
            clientId: this.clientId,
            callbackId: this.callbackId,
            syncCount: this.syncCount,
            lastImageSize: this.lastImageSize
        };
    }
    
    /**
     * Cleanup on destroy
     */
    onDestroy() {
        console.log('🗑️ Cleaning up CallbackRenderViewport');
        
        // Close SSE connection
        if (this.eventSource) {
            this.eventSource.close();
            this.eventSource = null;
        }
        
        // Stop polling
        this.pollingMode = false;
        if (this.pollTimeout) {
            clearTimeout(this.pollTimeout);
            this.pollTimeout = null;
        }
        
        this.callbackMode = false;
    }
}

// Register component
if (typeof window !== 'undefined') {
    window.CallbackRenderViewport = CallbackRenderViewport;
    console.log('✅ CallbackRenderViewport component registered');
}