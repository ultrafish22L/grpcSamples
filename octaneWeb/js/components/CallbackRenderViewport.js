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
 * - Configurable UI debug mode for status overlays
 * 
 * UI DEBUG MODE:
 * - Set uiDebugMode = true to show status overlays and mode indicators
 * - Use setUIDebugMode(enabled) to toggle at runtime
 * - Global function: toggleUIDebugMode() in browser console
 */

class CallbackRenderViewport extends OctaneComponent {
    constructor(element, client, stateManager, eventSystem) {
        super(element, client, stateManager);
        
        // Store event system for scene loading events
        this.eventSystem = eventSystem;
        
        // UI Debug Mode - controls visibility of status overlays and mode indicators
        this.uiDebugMode = false; // Set to true to enable debug UI elements
        
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
        this.frameCount = 0; // Track total frames processed
        this.debugSavePNG = false; // Debug mode to save PNG files
        
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
            
            // Wait for scene data to be loaded before starting render polling
            this.setupSceneLoadingListener();
            
            console.log('✅ CallbackRenderViewport initialized successfully (waiting for scene data)');
            
        } catch (error) {
            console.error('❌ Failed to initialize CallbackRenderViewport:', error);
            this.showError('Failed to initialize render viewport', error.message);
        }
    }
    
    /**
     * Setup listener for scene data loading completion
     */
    setupSceneLoadingListener() {
        // Listen for scene data loaded event
        this.eventSystem.on('sceneDataLoaded', (sceneItems) => {
            console.log('🎬 Scene data loaded, starting render polling...', sceneItems.length, 'items');
            this.startRenderPolling();
        });
        
        // Also listen for components fully initialized as fallback
        this.eventSystem.on('componentsFullyInitialized', () => {
            // Only start if scene data hasn't triggered it yet
            if (!this.callbackMode && !this.pollingMode) {
                console.log('🎬 Components initialized, starting render polling as fallback...');
                this.startRenderPolling();
            }
        });
    }
    
    /**
     * Start render polling (callback mode with fallback to polling)
     */
    async startRenderPolling() {
        try {
            // Try to start callback mode first
            const callbackSuccess = await this.startCallbackMode();
            
            if (!callbackSuccess) {
                // Fallback to polling mode
                console.log('📸 Falling back to polling mode');
                await this.startPollingMode();
            }
            
            console.log('🎯 Render polling started successfully');
            
        } catch (error) {
            console.error('❌ Failed to start render polling:', error);
            this.showError('Failed to start render polling', error.message);
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
        
        // Create status overlay (controlled by uiDebugMode)
        if (this.uiDebugMode) {
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
        }
        
        // Create mode indicator (controlled by uiDebugMode)
        if (this.uiDebugMode) {
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
        }
        

        
        // Assemble viewport
        this.viewport.appendChild(this.imageDisplay);
        if (this.uiDebugMode && this.statusOverlay) {
            this.viewport.appendChild(this.statusOverlay);
        }
        if (this.uiDebugMode && this.modeIndicator) {
            this.viewport.appendChild(this.modeIndicator);
        }
        this.element.appendChild(this.viewport);
        
        // Initial status (controlled by uiDebugMode)
        if (this.uiDebugMode) {
            this.updateStatus('Initializing callback system...');
            this.updateModeIndicator('INITIALIZING', '#ffa500');
        }
        
        console.log('✅ 2D viewport created');
    }
    
    /**
     * Start callback streaming mode
     */
    async startCallbackMode() {
        try {
            console.log('🚀 Attempting to start callback streaming mode...');
            
            // Register callback with proxy server
            const callbackUrl = `${this.client.serverUrl}/render/register-callback`;
            console.log(`🔗 Callback registration URL: ${callbackUrl}`);
            
            console.log('📤 Making callback registration request...');
            
            // Add timeout to prevent hanging
            const controller = new AbortController();
            const timeoutId = setTimeout(() => controller.abort(), 10000); // 10 second timeout
            
            const response = await fetch(callbackUrl, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                signal: controller.signal
            });
            
            clearTimeout(timeoutId);
            
            console.log(`📥 Callback registration response status: ${response.status}`);
            console.log(`📥 Callback registration response ok: ${response.ok}`);
            
            const result = await response.json();
            console.log('📥 Callback registration result:', result);
            
            if (!result.success) {
                throw new Error(result.error || 'Failed to register callback');
            }
            
            this.callbackId = result.callback_id;
            console.log(`✅ Callback registered with ID: ${this.callbackId}`);
            
            // Start Server-Sent Events stream
            const streamUrl = `${this.client.serverUrl}/render/stream`;
            this.eventSource = new EventSource(streamUrl);
            
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
                
                // Trigger Octane to render once streaming is connected
                this.triggerInitialRender();
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
            
            // console.log(`📸 OnNewImage callback #${this.callbackCount}:`, {
            //     callback_id: data.callback_id,
            //     images: data.render_images?.data?.length || 0,
            //     timestamp: data.timestamp
            // });
            
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
            this.frameCount++;
            
            // Clear existing content
            this.imageDisplay.innerHTML = '';
            
            console.log(`🖼️ Processing callback image #${this.frameCount}:`, {
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
            
            console.log(`🔍 Buffer analysis: ${bytes.length} bytes, first 16 bytes:`, 
                       Array.from(bytes.slice(0, 16)).map(b => b.toString(16).padStart(2, '0')).join(' '));
            
            // Convert buffer to RGBA format for canvas
            this.convertBufferToCanvas(bytes, imageData, imageDataObj);
            
            ctx.putImageData(imageDataObj, 0, 0);
            
            // DEBUG: Save PNG files to examine raw image data
            if (this.debugSavePNG) {
                this.savePNGDebug(canvas, this.frameCount);
            }
            
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
        
        // Check if buffer size matches expected size exactly (no padding)
        const expectedSize = width * height * 4;
        
        if (buffer.length === expectedSize) {
            console.log('✅ Perfect size match - direct copy');
            // Direct copy - no pitch issues
            for (let i = 0; i < expectedSize; i += 4) {
                data[i] = buffer[i];         // R
                data[i + 1] = buffer[i + 1]; // G
                data[i + 2] = buffer[i + 2]; // B
                data[i + 3] = buffer[i + 3]; // A
            }
        } else {
            console.log(`🔍 Size mismatch: buffer=${buffer.length}, expected=${expectedSize}, using pitch=${pitch}`);
            
            // Handle pitch (row stride) - pitch might be in pixels or bytes
            let pitchBytes;
            
            // Try pitch as bytes first
            if (pitch * height === buffer.length) {
                console.log(`🔍 Pitch is in bytes: ${pitch}`);
                pitchBytes = pitch;
            } else if (pitch * 4 * height === buffer.length) {
                console.log(`🔍 Pitch is in pixels: ${pitch} -> ${pitch * 4} bytes`);
                pitchBytes = pitch * 4;
            } else {
                console.log(`⚠️ Pitch calculation unclear, using width-based pitch`);
                pitchBytes = width * 4;
            }
            
            // Copy with pitch consideration
            for (let y = 0; y < height; y++) {
                for (let x = 0; x < width; x++) {
                    const srcIndex = y * pitchBytes + x * 4;
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
    }
    
    /**
     * Convert HDR RGBA buffer to canvas (simplified tone mapping)
     */
    convertHDRRGBA(buffer, width, height, pitch, canvasImageData) {
        const data = canvasImageData.data;
        // Create a new ArrayBuffer to avoid buffer reuse corruption
        const floatBuffer = new ArrayBuffer(buffer.length);
        const floatView = new Float32Array(floatBuffer);
        const uint8View = new Uint8Array(floatBuffer);
        
        // Copy the original buffer data
        uint8View.set(buffer);
        
        // Now reinterpret as floats safely
        
        // Check if buffer size matches expected size exactly (no padding)
        const expectedFloats = width * height * 4;
        
        if (floatView.length === expectedFloats) {
            console.log('✅ HDR Perfect size match - direct copy');
            // Direct copy - no pitch issues
            for (let i = 0; i < expectedFloats; i += 4) {
                // Simple tone mapping: clamp and convert to 8-bit
                data[i] = Math.min(255, Math.max(0, floatView[i] * 255));         // R
                data[i + 1] = Math.min(255, Math.max(0, floatView[i + 1] * 255)); // G
                data[i + 2] = Math.min(255, Math.max(0, floatView[i + 2] * 255)); // B
                data[i + 3] = Math.min(255, Math.max(0, floatView[i + 3] * 255)); // A
            }
        } else {
            console.log(`🔍 HDR Size mismatch: floats=${floatView.length}, expected=${expectedFloats}, using pitch=${pitch}`);
            
            // Handle pitch for HDR data - pitch might be in pixels or bytes
            let pitchFloats;
            
            // Try pitch as bytes first (convert to float count)
            if ((pitch / 4) * height === floatView.length) {
                console.log(`🔍 HDR Pitch is in bytes: ${pitch} -> ${pitch / 4} floats`);
                pitchFloats = pitch / 4;
            } else if (pitch * 4 * height === floatView.length) {
                console.log(`🔍 HDR Pitch is in pixels: ${pitch} -> ${pitch * 4} floats`);
                pitchFloats = pitch * 4;
            } else {
                console.log(`⚠️ HDR Pitch calculation unclear, using width-based pitch`);
                pitchFloats = width * 4;
            }
            
            // Copy with pitch consideration
            for (let y = 0; y < height; y++) {
                for (let x = 0; x < width; x++) {
                    const srcIndex = y * pitchFloats + x * 4;
                    const dstIndex = (y * width + x) * 4;
                    
                    if (srcIndex + 3 < floatView.length) {
                        // Simple tone mapping: clamp and convert to 8-bit
                        data[dstIndex] = Math.min(255, Math.max(0, floatView[srcIndex] * 255));     // R
                        data[dstIndex + 1] = Math.min(255, Math.max(0, floatView[srcIndex + 1] * 255)); // G
                        data[dstIndex + 2] = Math.min(255, Math.max(0, floatView[srcIndex + 2] * 255)); // B
                        data[dstIndex + 3] = Math.min(255, Math.max(0, floatView[srcIndex + 3] * 255)); // A
                    }
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
 /*       
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
*/            
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
        // RIGHT CLICK = ORBIT, LEFT CLICK = PAN, WHEEL = ZOOM
        this.viewport.addEventListener('mousedown', (e) => {
            if (e.button === 0) { // Left button = PAN
                this.mouse.panning = true;
                this.viewport.style.cursor = 'move';
            } else if (e.button === 2) { // Right button = ORBIT
                this.mouse.dragging = true;
                this.viewport.style.cursor = 'grabbing';
            }
            this.mouse.lastX = e.clientX;
            this.mouse.lastY = e.clientY;
            e.preventDefault();
        });
        
        this.viewport.addEventListener('mousemove', (e) => {
            if (this.mouse.dragging || this.mouse.panning) {
                const deltaX = e.clientX - this.mouse.lastX;
                const deltaY = e.clientY - this.mouse.lastY;
                
                if (this.mouse.dragging) {
                    // RIGHT CLICK: Orbit camera around target
                    this.camera.theta += deltaX * this.camera.sensitivity;
                    this.camera.phi += deltaY * this.camera.sensitivity;
                    this.camera.phi = Math.max(-Math.PI/2 + 0.1, Math.min(Math.PI/2 - 0.1, this.camera.phi));
                    
                    // console.log(`🔄 Orbiting: theta=${this.camera.theta.toFixed(2)}, phi=${this.camera.phi.toFixed(2)}`);
                    
                } else if (this.mouse.panning) {
                    // LEFT CLICK: Pan camera target
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
                    
                    console.log(`↔️ Panning: center=[${this.camera.center.map(v => v.toFixed(2)).join(', ')}]`);
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
            const oldRadius = this.camera.radius;
            this.camera.radius *= (1 + e.deltaY * this.camera.zoomSpeed * 0.001);
            this.camera.radius = Math.max(0.1, Math.min(1000, this.camera.radius));
            
            console.log(`🔍 Zooming: ${oldRadius.toFixed(2)} → ${this.camera.radius.toFixed(2)}`);
            
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
        if (!this.client.isReady()) return; // Don't sync when disconnected
        
        const now = Date.now();
        if (now - this.lastSyncTime < this.syncThrottle) return;
        
        try {
            // Calculate camera position
            const x = this.camera.center[0] + this.camera.radius * Math.cos(this.camera.phi) * Math.cos(this.camera.theta);
            const y = this.camera.center[1] + this.camera.radius * Math.sin(this.camera.phi);
            const z = this.camera.center[2] + this.camera.radius * Math.cos(this.camera.phi) * Math.sin(this.camera.theta);
            
            // Set camera parameters
            await this.client.setCameraPosition(x, y, z);
            await this.client.setCameraTarget(this.camera.center[0], this.camera.center[1], this.camera.center[2]);
            
            // CRITICAL: Call ApiChangeManager::update() to refresh Octane's display
            await this.triggerOctaneUpdate();
            
            this.lastSyncTime = now;
            this.syncCount++;
            
            console.log(`📷 Camera synced: pos=[${x.toFixed(2)}, ${y.toFixed(2)}, ${z.toFixed(2)}], target=[${this.camera.center.map(v => v.toFixed(2)).join(', ')}]`);
            
        } catch (error) {
            console.warn('⚠️ Camera sync error:', error);
        }
    }
    
    /**
     * Trigger Octane display update via ApiChangeManager::update()
     */
    async triggerOctaneUpdate() {
        try {
            // Call ApiChangeManager::update() to make Octane refresh its display
            const response = await this.client.makeGrpcCall('ApiChangeManager', 'update', {});
            // console.log('🔄 Octane display update triggered');
            
            return response;
        } catch (error) {
            console.warn('⚠️ Failed to trigger Octane update:', error);
            throw error;
        }
    }
    
    /**
     * Trigger initial render when callback streaming connects
     */
    async triggerInitialRender() {
        try {
            console.log('🎬 Triggering initial render via ApiChangeManager::update()');
            const response = await this.client.makeGrpcCall('ApiChangeManager', 'update', {});
            console.log('✅ Initial render triggered successfully');
            return response;
        } catch (error) {
            console.warn('⚠️ Failed to trigger initial render:', error);
            // Don't throw - this is not critical for callback streaming to work
        }
    }
    
    /**
     * Save PNG debug files to examine raw image data
     */
    savePNGDebug(canvas, frameNumber) {
        try {
            // Convert canvas to blob
            canvas.toBlob((blob) => {
                if (blob) {
                    // Create download link
                    const url = URL.createObjectURL(blob);
                    const link = document.createElement('a');
                    link.href = url;
                    link.download = `debug_frame_${frameNumber.toString().padStart(3, '0')}.png`;
                    
                    // Trigger download
                    document.body.appendChild(link);
                    link.click();
                    document.body.removeChild(link);
                    
                    // Clean up
                    URL.revokeObjectURL(url);
                    
                    console.log(`💾 DEBUG: Saved frame ${frameNumber} as PNG`);
                } else {
                    console.warn(`⚠️ DEBUG: Failed to create blob for frame ${frameNumber}`);
                }
            }, 'image/png');
        } catch (error) {
            console.error(`❌ DEBUG: Error saving PNG for frame ${frameNumber}:`, error);
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
     * Update status overlay (controlled by uiDebugMode)
     */
    updateStatus(message) {
        if (this.uiDebugMode && this.statusOverlay) {
            this.statusOverlay.textContent = message;
        }
    }
    
    /**
     * Update mode indicator (controlled by uiDebugMode)
     */
    updateModeIndicator(mode, color = '#666') {
        if (this.uiDebugMode && this.modeIndicator) {
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
     * Toggle UI debug mode at runtime
     */
    setUIDebugMode(enabled) {
        const wasEnabled = this.uiDebugMode;
        this.uiDebugMode = enabled;
        
        if (enabled && !wasEnabled) {
            // Enable debug UI - recreate elements
            this.createDebugUI();
        } else if (!enabled && wasEnabled) {
            // Disable debug UI - remove elements
            this.removeDebugUI();
        }
        
        console.log(`🎛️ UI Debug Mode ${enabled ? 'enabled' : 'disabled'}`);
    }

    /**
     * Create debug UI elements
     */
    createDebugUI() {
        if (!this.statusOverlay) {
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
            this.viewport.appendChild(this.statusOverlay);
        }

        if (!this.modeIndicator) {
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
            this.viewport.appendChild(this.modeIndicator);
        }

        // Update with current status
        this.updateStatus('Debug UI enabled');
        this.updateModeIndicator(this.callbackMode ? '🚀 CALLBACK MODE' : '📸 POLLING MODE', 
                                this.callbackMode ? '#00ff00' : '#ffa500');
    }

    /**
     * Remove debug UI elements
     */
    removeDebugUI() {
        if (this.statusOverlay) {
            this.statusOverlay.remove();
            this.statusOverlay = null;
        }
        if (this.modeIndicator) {
            this.modeIndicator.remove();
            this.modeIndicator = null;
        }
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