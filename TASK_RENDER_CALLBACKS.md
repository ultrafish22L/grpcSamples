# Task Document: Implement Render Engine Callbacks for 2D Image Display

## 🎯 OBJECTIVE
Add render engine callbacks to display live rendered images from Octane in the 2D viewport using the existing makeGrpcCall() infrastructure.

## 📋 CURRENT STATE
✅ **COMPLETED (v2.4)**:
- Live Octane LiveLink connection working
- Camera sync with mouse drag orbit and wheel zoom
- 2D viewport ready for image display
- makeGrpcCall() function working perfectly
- Debug console with full API call tracing

## 🚀 IMPLEMENTATION STRATEGY

### **Approach: Async Polling-Based Render Callbacks**
Use existing makeGrpcCall() function with intelligent async polling for simplicity and reliability.

**Why Async Polling?**
- **Virtually as good as streaming** when using async functions
- Leverages existing working infrastructure
- No proxy server modifications needed
- Simple to implement and debug
- Can optimize later without architectural changes
- Follows same pattern as camera sync
- Non-blocking performance with proper async/await

## 📝 IMPLEMENTATION PHASES

### **Phase 1: Image Display System** 🎯 **PRIORITY**
**Goal**: Display rendered images in 2D viewport - THE KEY FUNCTIONALITY

**Tasks**:
1. **Image Retrieval API Research & Implementation**
   - Research GetRenderImage, GetRenderBuffer, or similar APIs
   - Implement image data retrieval:
     ```javascript
     async getRenderImage(format = 'png', quality = 'preview')
     async getRenderBuffer()
     ```
   - Handle different image formats (PNG, JPEG, raw buffer)
   - Test with live Octane to understand data format

2. **Image Processing Pipeline**
   - Convert API response to displayable format
   - Handle base64 encoded images
   - Handle binary buffer data  
   - Add basic image caching to avoid redundant transfers

3. **2D Viewport Image Display**
   - Replace placeholder content with actual rendered image
   - Add image element to viewport HTML
   - Implement basic image scaling/fitting
   - Maintain aspect ratio
   - Handle image loading states (loading, error, success)

4. **Basic Async Polling for Images**
   - Implement simple async polling loop for image updates
   - Start with manual trigger (button click)
   - Use existing makeGrpcCall() pattern
   - Add basic error handling

**Success Criteria**:
- ✅ Rendered images appear in viewport
- ✅ Images load from live Octane API calls
- ✅ Image display replaces placeholder
- ✅ Basic async polling works
- ✅ Debug console shows image API calls

### **Phase 2: Render Control System**
**Goal**: Basic render start/stop functionality

**Tasks**:
1. **Add Render Control UI**
   - Add render control buttons to RenderViewport: Start, Stop, Refresh Image
   - Add render status indicator (Idle, Rendering, Complete)
   - Style buttons to match OTOY theme

2. **Implement Render API Calls**
   - Research Octane LiveLink render APIs (StartRender, StopRender)
   - Add render methods to LiveLinkClient:
     ```javascript
     async startRender(settings = {})
     async stopRender()
     ```
   - Use existing makeGrpcCall() pattern

3. **Render State Management**
   - Add render state tracking to RenderViewport
   - Handle render state transitions (idle → rendering → complete)
   - Update UI based on render state
   - Coordinate with image polling

**Success Criteria**:
- Render buttons appear in viewport
- StartRender API call succeeds (200 OK)
- StopRender API call succeeds
- Debug console shows render API calls
- Image polling starts/stops with render state

### **Phase 3: Progress Monitoring & Smart Polling**
**Goal**: Real-time render progress updates with intelligent async polling

**Tasks**:
1. **Add Progress Polling System**
   - Implement GetRenderProgress API call
   - Add intelligent async polling (fast during render, slow when idle)
   - Handle polling lifecycle (start/stop based on render state)
   - Coordinate progress polling with image polling

2. **Progress Data Display**
   - Update viewport status with:
     - Current samples count
     - Render time elapsed
     - Estimated completion percentage
     - Render resolution
   - Add progress bar or visual indicator

3. **Smart Async Polling Optimization**
   - Implement smart polling frequency:
     - 100ms during active rendering
     - 500ms for image updates during rendering
     - 1000ms when paused
     - Stop when idle
   - Use async/await for non-blocking performance
   - Error handling for failed progress calls

**Success Criteria**:
- Real-time sample count updates
- Render time display
- Smart async polling performs smoothly
- Progress polling coordinates with image updates
- No excessive API calls when idle

### **Phase 4: Optimization & Polish**
**Goal**: Performance optimization and user experience improvements

**Tasks**:
1. **Performance Optimization**
   - Implement image diff updates (only update changed regions)
   - Add image compression options
   - Optimize polling frequency based on render complexity
   - Add render quality settings (preview vs. final)

2. **User Experience Enhancements**
   - Add render presets (quick preview, production quality)
   - Add render queue management
   - Add render history/thumbnails
   - Add export options (save image, copy to clipboard)

3. **Error Handling & Recovery**
   - Handle render failures gracefully
   - Add retry logic for failed API calls
   - Add connection recovery during long renders
   - Add user notifications for render events

**Success Criteria**:
- Smooth performance during long renders
- Minimal network bandwidth usage
- Professional user experience
- Robust error handling

## 🔧 TECHNICAL IMPLEMENTATION DETAILS

### **API Integration Pattern**
Follow the existing camera sync pattern:

```javascript
// In LiveLinkClient class
async startRender(settings = {}) {
    const request = {
        width: settings.width || 1920,
        height: settings.height || 1080,
        samples: settings.samples || 1000,
        ...settings
    };
    
    const result = await this.makeGrpcCall('StartRender', request);
    return result && result.success ? result.data : null;
}

async getRenderProgress() {
    const request = {};
    const result = await this.makeGrpcCall('GetRenderProgress', request);
    return result && result.success ? result.data : null;
}

async getRenderImage(format = 'png') {
    const request = { format: format };
    const result = await this.makeGrpcCall('GetRenderImage', request);
    return result && result.success ? result.data : null;
}
```

### **Polling System Architecture**
```javascript
class RenderProgressPoller {
    constructor(client, viewport) {
        this.client = client;
        this.viewport = viewport;
        this.polling = false;
        this.pollInterval = null;
    }
    
    start() {
        if (this.polling) return;
        this.polling = true;
        this.poll();
    }
    
    stop() {
        this.polling = false;
        if (this.pollInterval) {
            clearTimeout(this.pollInterval);
        }
    }
    
    async poll() {
        if (!this.polling) return;
        
        try {
            const progress = await this.client.getRenderProgress();
            this.viewport.updateProgress(progress);
            
            // Smart polling frequency
            const delay = this.getPollingDelay(progress);
            this.pollInterval = setTimeout(() => this.poll(), delay);
        } catch (error) {
            console.error('Progress polling error:', error);
            // Retry with longer delay
            this.pollInterval = setTimeout(() => this.poll(), 2000);
        }
    }
    
    getPollingDelay(progress) {
        if (!progress) return 1000;
        if (progress.state === 'rendering') return 100;
        if (progress.state === 'paused') return 1000;
        return 2000; // idle or complete
    }
}
```

### **Image Display Integration**
```javascript
// In RenderViewport class
updateRenderImage(imageData) {
    if (!imageData) return;
    
    // Handle different image formats
    let imageSrc;
    if (imageData.format === 'base64') {
        imageSrc = `data:image/png;base64,${imageData.data}`;
    } else if (imageData.format === 'url') {
        imageSrc = imageData.url;
    }
    
    // Update viewport image
    const imageElement = this.container.querySelector('.render-image');
    if (imageElement) {
        imageElement.src = imageSrc;
        imageElement.style.display = 'block';
    }
    
    // Hide placeholder
    const placeholder = this.container.querySelector('.render-placeholder');
    if (placeholder) {
        placeholder.style.display = 'none';
    }
}
```

## 🎯 SUCCESS METRICS

### **Phase 1 Success** 🎯 **PRIORITY**:
- [ ] Rendered images display in viewport
- [ ] Images load from live Octane API calls
- [ ] Image display replaces placeholder
- [ ] Basic async polling works
- [ ] Debug console shows image API calls

### **Phase 2 Success**:
- [ ] Render control buttons functional
- [ ] StartRender API call returns 200 OK
- [ ] StopRender API call returns 200 OK
- [ ] Debug console shows render API calls
- [ ] Image polling starts/stops with render state

### **Phase 3 Success**:
- [ ] Real-time progress updates (samples, time)
- [ ] Smart async polling performs smoothly
- [ ] Progress polling coordinates with image updates
- [ ] No excessive API calls when idle
- [ ] Error handling for failed progress calls

### **Phase 4 Success**:
- [ ] Smooth performance during long renders
- [ ] Optimized network usage
- [ ] Professional user experience
- [ ] Robust error handling and recovery

## 🔍 RESEARCH TASKS

### **Before Implementation**:
1. **API Discovery**: Research available Octane LiveLink render APIs
   - Check proxy server for render-related endpoints
   - Test API calls manually to understand data formats
   - Document API parameters and responses

2. **Image Format Analysis**: Understand Octane image output formats
   - Test different image formats (PNG, JPEG, raw)
   - Analyze image data structure in API responses
   - Determine optimal format for web display

3. **Performance Baseline**: Establish performance expectations
   - Test polling frequency impact on system performance
   - Measure image transfer times for different sizes
   - Identify potential bottlenecks

## 🚨 RISK MITIGATION

### **Potential Issues**:
1. **Unknown API Names**: Octane render APIs might have different names
   - **Mitigation**: Research existing proxy endpoints, test manually
   
2. **Image Format Complexity**: Image data might be in complex formats
   - **Mitigation**: Start with simple formats, add complexity gradually
   
3. **Performance Impact**: Polling might impact system performance
   - **Mitigation**: Implement smart polling, add performance monitoring
   
4. **Network Bandwidth**: Large images might cause bandwidth issues
   - **Mitigation**: Add image compression, implement progressive loading

### **Fallback Plans**:
- If render APIs unavailable: Implement mock render system for development
- If image display fails: Show progress-only mode
- If polling causes issues: Reduce frequency or implement manual refresh

## 📚 REFERENCE MATERIALS

### **Existing Code Patterns**:
- `LiveLinkClient.setCamera()` - API call pattern
- `RenderViewport.handleMouseDown()` - Event handling pattern  
- `OctaneWebClient.makeGrpcCall()` - gRPC call implementation
- Debug console logging - Error handling and debugging

### **Files to Modify**:
- `octaneWeb/shared/js/livelink.js` - Add render API methods
- `octaneWeb/js/components/RenderViewport.js` - Add render UI and image display
- `octaneWeb/css/main.css` - Style render controls and progress indicators

### **Files to Create**:
- `octaneWeb/js/utils/RenderProgressPoller.js` - Polling system (optional)
- `octaneWeb/js/utils/ImageProcessor.js` - Image handling utilities (optional)

## 🎉 EXPECTED OUTCOME

After **Phase 1** completion (the key phase), users will be able to:
1. **View rendered images** from Octane in the 2D viewport ⭐ **CORE FUNCTIONALITY**
2. **See live image updates** through async polling
3. **Experience smooth performance** with non-blocking async calls

After **full completion**, users will be able to:
1. **View rendered images** as they develop in the 2D viewport ⭐
2. **Start renders** directly from the web interface  
3. **Monitor progress** in real-time with sample counts and timing
4. **Control render quality** and settings through the UI
5. **Experience smooth performance** during long render sessions

This will make octaneWeb a complete LiveLink interface matching Octane Studio's render capabilities while maintaining the simplicity and reliability of the existing makeGrpcCall() architecture.

## 💡 KEY INSIGHT
**Async polling is virtually as good as streaming** - the non-blocking nature of async/await means the UI remains responsive while continuously polling for updates, providing a streaming-like experience without the complexity of WebSocket or Server-Sent Events infrastructure.