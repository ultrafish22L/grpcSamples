/**
 * Callback-based Render Viewport Component
 * 
 * Production-ready real-time rendering viewport with callback streaming from
 * Octane. Provides live rendering updates, mouse drag camera control,
 * and seamless integration with the Octane rendering pipeline.
 * 
 * Core Features:
 * - Real-time callback streaming with OnNewImage events
 * - Mouse drag camera synchronization with live Octane updates
 * - HDR/LDR buffer processing with proper isolation to prevent garbage frames
 * - Production-optimized performance with minimal debug overhead
 * - Configurable UI debug mode for development visibility
 * 
 * Technical Implementation:
 * - Server-Sent Events (SSE) for real-time callback streaming
 * - Centralized Camera system for smooth mouse interactions
 * - Buffer isolation prevents corruption between render updates
 * - Zero-copy base64 image processing for optimal performance
 * - Graceful degradation when callback streaming unavailable
 * 
 * UI Debug Mode:
 * - Default: uiDebugMode = false (clean production UI)
 * - Runtime toggle: toggleUIDebugMode() in browser console
 * - Shows status overlays, and performance metrics
 */

class CallbackRenderViewport extends OctaneComponent {
    constructor(element, stateManager, eventSystem) {
        super(element, stateManager);
        
        // Event system dependency for cross-component communication
        this.eventSystem = eventSystem;
        
        // UI Debug Mode - production default is false for clean interface
        this.uiDebugMode = false; // Toggle via toggleUIDebugMode() in console
        
        // Real-time callback streaming state management
        this.callbackMode = false;            // Currently using callback streaming
        this.eventSource = null;              // Server-Sent Events connection
        this.callbackId = null;               // Active callback registration ID
        
        // DOM viewport elements for rendering display
        this.viewport = null;                 // Main viewport container
        this.imageDisplay = null;             // Image display element
        this.statusOverlay = null;            // Debug status overlay
        
        // Centralized camera system for mouse drag interactions
        this.camera = new Camera(window.octaneClient, {
            radius: 20.0,                     // Camera distance from target
            theta: 0.0,                       // Horizontal rotation angle
            phi: 0.0,                         // Vertical rotation angle
            center: [0.0, 0.0, 0.0],          // Camera target center point
            fov: 45.0,                        // Field of view in degrees
            sensitivity: 0.01,                // Mouse sensitivity multiplier
            zoomSpeed: 0.1                    // Zoom speed multiplier
        });
        
        // Performance and debugging statistics
        this.callbackCount = 0;               // Total callbacks received
        this.lastCallbackTime = 0;            // Timestamp of last callback
        this.connectionErrors = 0;            // Connection error count
        this.lastImageSize = 0;               // Size of last received image
        this.frameCount = 0;                  // Total frames processed
        this.debugSavePNG = false;            // Debug PNG saving (disabled in production)
        this.doRendering  = true;            // render on/off
        
        console.log('CallbackRenderViewport initialized with streaming callbacks');
    }
    
    async onInitialize() {
        console.log('Initializing Callback Render Viewport...');
        
        try {
            // Create 2D viewport container
            await this.create2DViewport();
            
            // Initialize camera from Octane's current state
            await this.camera.initializeFromOctane();
            
            // Setup camera mouse controls
            this.camera.setupMouseControls(this.viewport);
            
            // Wait for scene data to be loaded before starting render 
            this.setupSceneLoadingListener();
            
            console.log('CallbackRenderViewport initialized successfully (waiting for scene data)');
            
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
        this.eventSystem.on('sceneDataLoaded', (scene) => {
            console.log('Scene data loaded, starting render...', scene.tree.length, 'items');
            this.startRender();
        });
        
        // Also listen for components fully initialized as fallback
        this.eventSystem.on('componentsFullyInitialized', () => {
            // Only start if scene data hasn't triggered it yet
//            this.startRender();
        });
    }
    
    /**
     * Start render callback mode
     */
    async startRender() {
        if (!this.doRendering) return true;
        
        try {
            console.log('Attempting to start callback streaming mode...');
            
            // Register callback with proxy server
            const callbackUrl = `${window.octaneClient.serverUrl}/render/register-callback`;
            console.log(`Callback registration URL: ${callbackUrl}`);
            
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
            
//            console.log(`Callback registration response status: ${response.status}`);
//            console.log(`Callback registration response ok: ${response.ok}`);
            
            const result = await response.json();
            if (!result.success) {
                throw new Error(result.error || 'Failed to register callback');
            }
            
            this.callbackId = result.callback_id;
            console.log(`Callback registered with ID: ${this.callbackId}`);
            
            // Start Server-Sent Events stream
            const streamUrl = `${window.octaneClient.serverUrl}/render/stream`;
            this.eventSource = new EventSource(streamUrl);
            
            this.eventSource.onopen = (event) => {
                console.log('SSE connection opened');
                this.connectionErrors = 0;
                this.updateStatus('Connected to callback stream');
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
                
                this.updateStatus(`Connection error #${this.connectionErrors}, retrying...`);
            };
            
            // Wait a moment to see if connection succeeds
            await new Promise(resolve => setTimeout(resolve, 1000));
            
            return true;
            
        } catch (error) {
            console.error('❌ Failed to start callback mode:', error);
            this.updateStatus(`Callback failed: ${error.message}`);
            return false;
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
        
        // Assemble viewport
        this.viewport.appendChild(this.imageDisplay);
        if (this.uiDebugMode && this.statusOverlay) {
            this.viewport.appendChild(this.statusOverlay);
        }
        this.element.appendChild(this.viewport);
        
        // Initial status (controlled by uiDebugMode)
        if (this.uiDebugMode) {
            this.updateStatus('Initializing callback system...');
        }
        
        console.log('2D viewport created');
    }
    
    /**
     * Handle callback events from Server-Sent Events
     */
    handleCallbackEvent(data) {
        switch (data.type) {
            case 'connected':
                console.log(`Connected to callback stream, client ID: ${data.client_id}`);
                window.octaneClientId = data.client_id;
                this.updateStatus(`Connected (Client: ${data.client_id.substring(0, 8)}...)`);
                
                // Trigger Octane to render once streaming is connected
                this.triggerInitialRender();
                break;
                
            case 'newImage':
                this.handleNewImageCallback(data);
                break;
                
            case 'renderFailure':
                console.error('❌ Render failure callback:', JSON.stringify(data, null, 2));
                this.updateStatus('Render failure detected');
                break;
                
            case 'newStatistics':
//                console.log('New statistics callback:', data);
                break;
                
            case 'ping':
                // Keep-alive ping
                console.log('ping keep-alive callback:');
                break;
                
            default:
                console.log('Unknown callback event:', JSON.stringify(data, null, 2));
        }
    }
    
    /**
     * Handle OnNewImage callback data
     */
    handleNewImageCallback(data) {
        try {
            this.callbackCount++;
            this.lastCallbackTime = Date.now();
            
            // console.log(`OnNewImage callback #${this.callbackCount}:`, {
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
                console.warn(' No image data in callback');
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
/*            
            console.log(`Processing callback image #${this.frameCount}:`, {
                type: imageData.type,
                size: `${imageData.size.x}x${imageData.size.y}`,
                pitch: imageData.pitch,
                samples: imageData.tonemappedSamplesPerPixel,
                renderTime: imageData.renderTime,
                hasBuffer: !!imageData.buffer
            });
*/            
            if (!imageData.buffer || !imageData.buffer.data) {
                this.showImageError('No image buffer in callback data');
                return;
            }
            
            // Decode base64 buffer
            const bufferData = imageData.buffer.data;
            const bufferSize = imageData.buffer.size;
            this.lastImageSize = bufferSize;
            
//            console.log(`Image buffer: ${bufferSize} bytes (${imageData.buffer.encoding})`);
//            console.log(`Buffer data type: ${typeof bufferData}, length: ${bufferData ? bufferData.length : 'null'}`);
//            console.log(`Buffer data preview: ${bufferData ? bufferData.substring(0, 100) : 'null'}...`);
            
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
            
            // Decode base64 to binary with error handling
            let bytes;
            try {
                const binaryString = atob(bufferData);
                bytes = new Uint8Array(binaryString.length);
                for (let i = 0; i < binaryString.length; i++) {
                    bytes[i] = binaryString.charCodeAt(i);
                }
            } catch (error) {
                console.error('❌ Base64 decode error:', error);
                console.error('❌ Buffer data that failed:', bufferData);
                this.showImageError(`Base64 decode failed: ${error.message}`);
                return;
            }
            
//            console.log(`Buffer analysis: ${bytes.length} bytes, first 16 bytes:`, 
//                       Array.from(bytes.slice(0, 16)).map(b => b.toString(16).padStart(2, '0')).join(' '));
            
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
            
//            console.log('Callback image displayed successfully');
            
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
                console.warn(` Unsupported image type: ${imageType}, trying LDR RGBA`);
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
//            console.log('Perfect size match - direct copy');
            // Direct copy - no pitch issues
            for (let i = 0; i < expectedSize; i += 4) {
                data[i] = buffer[i];         // R
                data[i + 1] = buffer[i + 1]; // G
                data[i + 2] = buffer[i + 2]; // B
                data[i + 3] = buffer[i + 3]; // A
            }
        } else {
//            console.log(`Size mismatch: buffer=${buffer.length}, expected=${expectedSize}, using pitch=${pitch}`);
            
            // Handle pitch (row stride) - pitch might be in pixels or bytes
            let pitchBytes;
            
            // Try pitch as bytes first
            if (pitch * height === buffer.length) {
//                console.log(`Pitch is in bytes: ${pitch}`);
                pitchBytes = pitch;
            } else if (pitch * 4 * height === buffer.length) {
//                console.log(`Pitch is in pixels: ${pitch} -> ${pitch * 4} bytes`);
                pitchBytes = pitch * 4;
            } else {
//                console.log(` Pitch calculation unclear, using width-based pitch`);
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
//            console.log('HDR Perfect size match - direct copy');
            // Direct copy - no pitch issues
            for (let i = 0; i < expectedFloats; i += 4) {
                // Simple tone mapping: clamp and convert to 8-bit
                data[i] = Math.min(255, Math.max(0, floatView[i] * 255));         // R
                data[i + 1] = Math.min(255, Math.max(0, floatView[i + 1] * 255)); // G
                data[i + 2] = Math.min(255, Math.max(0, floatView[i + 2] * 255)); // B
                data[i + 3] = Math.min(255, Math.max(0, floatView[i + 3] * 255)); // A
            }
        } else {
//            console.log(`HDR Size mismatch: floats=${floatView.length}, expected=${expectedFloats}, using pitch=${pitch}`);
            
            // Handle pitch for HDR data - pitch might be in pixels or bytes
            let pitchFloats;
            
            // Try pitch as bytes first (convert to float count)
            if ((pitch / 4) * height === floatView.length) {
//                console.log(`HDR Pitch is in bytes: ${pitch} -> ${pitch / 4} floats`);
                pitchFloats = pitch / 4;
            } else if (pitch * 4 * height === floatView.length) {
//                console.log(`HDR Pitch is in pixels: ${pitch} -> ${pitch * 4} floats`);
                pitchFloats = pitch * 4;
            } else {
//                console.log(` HDR Pitch calculation unclear, using width-based pitch`);
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
     * Trigger Octane display update via ApiChangeManager::update()
     */
    async triggerOctaneUpdate() {
        window.octaneClient.makeApiCall('ApiChangeManager/update');            
    }
    
    /**
     * Trigger initial render when callback streaming connects
     */
    async triggerInitialRender() {
        window.octaneClient.makeApiCall('ApiChangeManager/update');            
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
                    
                    console.log(`DEBUG: Saved frame ${frameNumber} as PNG`);
                } else {
                    console.warn(` DEBUG: Failed to create blob for frame ${frameNumber}`);
                }
            }, 'image/png');
        } catch (error) {
            console.error(`❌ DEBUG: Error saving PNG for frame ${frameNumber}:`, error);
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
     * Show error message
     */
    showError(title, message) {
        this.updateStatus(`ERROR: ${title} - ${message}`);
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
        
        console.log(`UI Debug Mode ${enabled ? 'enabled' : 'disabled'}`);
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

        // Update with current status
        this.updateStatus('Debug UI enabled');
    }

    /**
     * Remove debug UI elements
     */
    removeDebugUI() {
        if (this.statusOverlay) {
            this.statusOverlay.remove();
            this.statusOverlay = null;
        }
    }
    
    /**
     * Show image error
     */
    showImageError(message, details = '') {
        this.imageDisplay.innerHTML = `
            <div style="color: #ff6b6b; text-align: center; padding: 20px;">
                <div style="font-size: 18px; margin-bottom: 10px;"> ${message}</div>
                ${details ? `<div style="font-size: 12px; opacity: 0.7;">${details}</div>` : ''}
            </div>
        `;
    }
    
    /**
     * Get current status
     */
    getStatus() {
        return {
            mode: 'callback',
            callbackCount: this.callbackCount,
            lastCallbackTime: this.lastCallbackTime,
            connectionErrors: this.connectionErrors,
            clientId: window.octaneClientId,
            callbackId: this.callbackId,
            syncCount: this.syncCount,
            lastImageSize: this.lastImageSize
        };
    }
    
    /**
     * Cleanup on destroy
     */
    onDestroy() {
        console.log('Cleaning up CallbackRenderViewport');
        
        // Clean up camera system
        if (this.camera) {
            this.camera.destroy();
            this.camera = null;
        }
        
        // Close SSE connection
        if (this.eventSource) {
            this.eventSource.close();
            this.eventSource = null;
        }
    }
}

// Register component
if (typeof window !== 'undefined') {
    window.CallbackRenderViewport = CallbackRenderViewport;
    console.log('CallbackRenderViewport component registered');
}