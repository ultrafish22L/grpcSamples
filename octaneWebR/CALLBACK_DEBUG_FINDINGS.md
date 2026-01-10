# Callback Viewport Debug Session Findings
**Date**: 2025-01-20
**Issue**: Render viewport blank despite OnNewImage callbacks firing

## 🔍 Investigation Summary

### Server Log Analysis
```
📡 Registering OnNewImage callback with ID: 934689
❌ Failed to register callback: 2 UNKNOWN: Unexpected error in RPC handling
   (Callbacks will not work until Octane is running and LiveLink is enabled)
```

**Finding 1**: In sandbox environment, Octane is not available, so callbacks cannot be tested.

### WebSocket Connection Analysis

**Expected Server Logs** (not seen):
```
🔌 WebSocket client connected
📡 Client subscribed to callbacks
```

**Finding 2**: WebSocket is NOT connecting!

### Root Cause Analysis

#### The Problem: Health Check Blocking

**File**: `client/src/services/OctaneClient.ts`, lines 70-104

```typescript
async connect(): Promise<boolean> {
  // 1. Health check (line 73)
  const healthResponse = await fetch(healthUrl, ...);
  
  // 2. WebSocket connection (line 90) - ONLY CALLED IF HEALTH CHECK PASSES
  this.connectWebSocket();
  
  // 3. Set connected state (line 92)
  this.connected = true;
}
```

**File**: `vite-plugin-octane-grpc.ts`, lines 255-263

```typescript
async checkHealth(): Promise<boolean> {
  try {
    // 5 SECOND TIMEOUT if Octane not running
    await this.callMethod('ApiProjectManager', 'rootNodeGraph', {}, { timeout: 5000 });
    return true;
  } catch (error) {
    return false;
  }
}
```

**The Flow**:
1. Client calls `/api/health`
2. Server calls Octane's `rootNodeGraph` with 5s timeout
3. If Octane not running (sandbox): Takes 5 seconds, returns failure
4. Client's health check fails
5. `connect()` throws error **before calling** `connectWebSocket()`
6. **WebSocket never connects!**

## 🎯 Why User Sees Different Behavior

**User Environment** (with Octane):
- Health check passes quickly ✅
- WebSocket connects ✅
- OnNewImage callbacks ARE firing ✅
- **But viewport still blank** ❓

**This suggests a different issue**: Data structure mismatch or canvas rendering problem.

## 🔬 Data Flow Analysis

### Expected Data Structure

**Vite Plugin** (vite-plugin-octane-grpc.ts, line 324-329):
```typescript
const imageData = {
  callback_source: callbackRequest.newImage.callback_source,
  callback_id: callbackRequest.newImage.callback_id,
  user_data: callbackRequest.newImage.user_data,
  render_images: callbackRequest.newImage.render_images
};
this.notifyCallbacks(imageData);
```

**WebSocket Send** (line 467):
```typescript
ws.send(JSON.stringify({ type: 'newImage', data }));
```

**Client Receives** (OctaneClient.ts, line 121-128):
```typescript
if (message.type === 'newImage') {
  this.emit('OnNewImage', message.data);
}
```

**Viewport Expects** (CallbackRenderViewport.tsx, line 410):
```typescript
if (data.render_images && data.render_images.data && data.render_images.data.length > 0) {
  displayCallbackImage(data.render_images.data[0]);
}
```

### Potential Mismatch

**Question**: Does `callbackRequest.newImage.render_images` have this structure?
```typescript
{
  data: [ /* array of OctaneImageData */ ]
}
```

**Or is it already an array?**
```typescript
[ /* array of OctaneImageData */ ]
```

**If it's already an array**, then the viewport check on line 410 will fail because:
- `data.render_images` exists ✅
- `data.render_images.data` is undefined ❌ (because render_images IS the array)

## 🎬 Action Items

### For Testing in User Environment (with Octane running):

1. **Check browser console for these logs**:
   ```
   🔌 Connecting WebSocket: ws://localhost:43929/api/callbacks
   ✅ WebSocket connected
   📥 [OctaneClient] Received OnNewImage via WebSocket
   🖼️  [CallbackViewport] OnNewImage event received
   🖼️  [CallbackViewport] Data: {hasRenderImages: true, hasData: ?, imageCount: ?}
   ```

2. **Look for this specific log**:
   ```
   🖼️  [CallbackViewport] Data: {
     hasRenderImages: true,
     hasData: false,  // <-- If FALSE, this is the bug!
     imageCount: undefined
   }
   ```

3. **If `hasData: false`**, the fix is:
   ```typescript
   // In CallbackRenderViewport.tsx, line 410
   // OLD:
   if (data.render_images && data.render_images.data && data.render_images.data.length > 0)
   
   // NEW: Handle both structures
   const images = Array.isArray(data.render_images) 
     ? data.render_images 
     : data.render_images?.data;
     
   if (images && images.length > 0) {
     displayCallbackImage(images[0]);
   }
   ```

### For Sandbox Testing (Octane not available):

**Cannot test callbacks without Octane**, but can verify:
1. ✅ Build passes
2. ✅ TypeScript compiles
3. ✅ Page loads
4. ✅ Connection status updates
5. ❌ Cannot test WebSocket or callbacks

## 📊 Diagnostic Commands

### Check WebSocket Connection (user environment only):
```javascript
// In browser console:
const ws = new WebSocket('ws://localhost:43929/api/callbacks');
ws.onopen = () => console.log('✅ WS connected');
ws.onmessage = (e) => console.log('📥 Message:', e.data);
ws.onerror = (e) => console.error('❌ WS error:', e);
```

### Check Data Structure:
```javascript
// Add this to CallbackRenderViewport.tsx, line 401:
console.log('🔍 Full callback data:', JSON.stringify(data, null, 2));
```

## ✅ Conclusion

**In Sandbox**: Cannot test callbacks (Octane not running)
**In User Environment**: Likely data structure mismatch in `render_images`

**Most Likely Fix**: Update CallbackRenderViewport to handle both:
- `data.render_images.data` (expected)
- `data.render_images` (possibly what's actually sent)
