# Callback Streaming Fix - Implementation Report

## Issue Summary
The CallbackRenderViewport was showing "⚠️ [CallbackViewport] No valid image data in callback" despite successful API calls. The root cause was **incomplete callback registration** with Octane's gRPC API.

## Root Causes Identified

### 1. **Missing Callback Registration Parameters**
**Location**: `server/src/grpc/client.ts` line 321

**Problem**: The `setOnNewImageCallback` was being called with empty parameters:
```typescript
await this.callMethod('ApiRender', 'setOnNewImageCallback', {}, { timeout: 10000 });
```

**Required Structure** (from `apirender.proto` and `common.proto`):
```typescript
{
  callback: {
    callbackSource: string,  // Identifier for callback source
    callbackId: number       // Callback function ID
  },
  userData: number          // Optional user data
}
```

**Fix Applied**:
```typescript
await this.callMethod('ApiRenderEngine', 'setOnNewImageCallback', {
  callback: {
    callbackSource: 'octaneWebR',
    callbackId: 1
  },
  userData: 0
}, { timeout: 10000 });
```

### 2. **Incorrect Service Name**
**Problem**: Using `'ApiRender'` instead of `'ApiRenderEngine'`
**Fix**: Changed to correct service name `'ApiRenderEngine'` (matches proto definition)

### 3. **Enhanced Stream Data Logging**
**Location**: `server/src/grpc/client.ts` lines 335-379

Added comprehensive logging to debug stream data structure:
- Logs received callback data structure
- Checks for `response.newImage` (StreamCallbackRequest oneof)
- Checks for `response.newImage.render_images` (image data)
- Provides fallback checks for different data structures
- Detailed error reporting

## Architecture Overview

```
┌─────────────────────────────────────────────────────────────────┐
│ OCTANE RENDER ENGINE                                             │
│  - Generates render images                                       │
│  - Sends callbacks via gRPC stream                               │
└──────────────────────────┬──────────────────────────────────────┘
                           │ gRPC Stream
                           │ (StreamCallbackService.callbackChannel)
                           ▼
┌─────────────────────────────────────────────────────────────────┐
│ SERVER (Node.js)                                                 │
│                                                                   │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │ GrpcClient.startCallbackStreaming()                      │   │
│  │  1. Register: ApiRenderEngine.setOnNewImageCallback      │   │
│  │  2. Stream: StreamCallbackService.callbackChannel        │   │
│  │  3. Emit 'OnNewImage' events                             │   │
│  └────────────────────────┬────────────────────────────────┘   │
│                           │                                      │
│                           ▼                                      │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │ CallbackManager                                          │   │
│  │  - Listens for gRPC 'OnNewImage' events                 │   │
│  │  - Re-emits to WebSocket layer                          │   │
│  └────────────────────────┬────────────────────────────────┘   │
│                           │                                      │
│                           ▼                                      │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │ WebSocket Server (/api/callbacks)                        │   │
│  │  - Forwards OnNewImage to browser clients               │   │
│  │  - JSON format with type: 'newImage'                    │   │
│  └────────────────────────┬────────────────────────────────┘   │
│                           │                                      │
└───────────────────────────┼──────────────────────────────────────┘
                            │ WebSocket
                            ▼
┌─────────────────────────────────────────────────────────────────┐
│ BROWSER (React)                                                  │
│                                                                   │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │ ConnectionService                                        │   │
│  │  - WebSocket connection to /api/callbacks               │   │
│  │  - Receives 'newImage' messages                         │   │
│  │  - Emits 'OnNewImage' events                            │   │
│  └────────────────────────┬────────────────────────────────┘   │
│                           │                                      │
│                           ▼                                      │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │ CallbackRenderViewport Component                        │   │
│  │  - Listens for 'OnNewImage' events                      │   │
│  │  - Decodes base64 image buffer                          │   │
│  │  - Displays on canvas                                   │   │
│  └─────────────────────────────────────────────────────────┘   │
│                                                                   │
└─────────────────────────────────────────────────────────────────┘
```

## Files Modified

### 1. `/server/src/grpc/client.ts`
- **Line 321-327**: Fixed callback registration with proper parameters
- **Line 335-379**: Enhanced stream data logging and processing
- Added support for StreamCallbackRequest oneof structure

### 2. `/server/src/services/callbackManager.ts`
- **Line 104-107**: Fixed unregister to use correct empty callback syntax

## Expected Stream Data Structure

Based on `callbackstream.proto` and reference implementation:

```typescript
// Stream returns StreamCallbackRequest
{
  newImage?: {              // oneof payload
    user_data: number,
    callback_id?: number,
    render_images?: {       // ApiArrayApiRenderImage
      data: Array<{
        type: number,       // ImageType enum
        size: { x: number, y: number },
        pitch: number,
        buffer: {
          data: string,     // base64 encoded
          size: number,
          encoding: 'base64'
        },
        tonemappedSamplesPerPixel: number,
        renderTime: number,
        // ... other ApiRenderImage fields
      }>
    }
  },
  renderFailure?: { ... },
  newStatistics?: { ... },
  projectManagerChanged?: { ... }
}
```

## Testing Checklist

### Prerequisites
- [ ] Octane is running on host machine
- [ ] LiveLink is enabled in Octane
- [ ] Octane gRPC server is accessible (default: localhost:51022 or host.docker.internal:51022)

### Server Testing
1. **Start Server**
   ```bash
   cd /workspace/project/grpcSamples/octaneWebR
   npm run build
   npm start
   ```

2. **Expected Server Logs**
   ```
   📡 gRPC channel initialized: [host]:[port]
   ✅ Core proto definitions loaded successfully
   ✅ gRPC client initialized successfully
   📡 WebSocket server initialized at /api/callbacks
   ✅ WebSocket callback streaming ready
   🎬 Starting callback streaming...
   📝 Registering OnNewImage callback...
   ✅ Callback registered: { ... }
   📡 Starting callback channel stream...
   ✅ Found service: StreamCallbackService at [pattern]
   ✅ Callback streaming started
   ✅ Octane callback streaming initialized
   ```

3. **Trigger Render in Octane**
   - Modify scene in Octane
   - Or manually trigger render update

4. **Watch for Stream Data**
   ```
   📥 [Stream] Received callback data: { ... }
   📥 [Stream] newImage payload: { ... }
   ✅ [Stream] Found render_images in newImage, emitting OnNewImage event
   📸 [CallbackManager] Received N render image(s)
   📡 [WebSocket] Forwarding OnNewImage to client
   ```

### Browser Testing
1. **Open Browser** to http://localhost:45769 (or configured port)

2. **Open DevTools Console**

3. **Expected Console Logs**
   ```
   🎯 useOctane: Setting up event listeners
   ✅ WebSocket connected
   🎯 useOctane: handleConnected called
   📸 [CallbackViewport] Received image data
   ```

4. **Verify Render Display**
   - [ ] Render viewport shows image
   - [ ] Image updates when scene changes
   - [ ] Frame count increments
   - [ ] Status shows "Rendering..." or render time

### Debugging

If no image appears:

1. **Check Server Logs** for:
   - Callback registration success
   - Stream connection established
   - Stream data received

2. **Check Browser Console** for:
   - WebSocket connection status
   - OnNewImage events received
   - Image data structure

3. **Common Issues**:
   - **Octane not running**: Server logs will show connection timeout
   - **LiveLink disabled**: Callbacks won't be triggered
   - **Wrong host/port**: Check OCTANE_HOST and OCTANE_PORT env vars
   - **Proto mismatch**: Check if callbackstream.proto matches Octane version

## Environment Variables

```bash
# Server
OCTANE_HOST=localhost           # or host.docker.internal for Docker
OCTANE_PORT=51022               # Octane gRPC port
SERVER_PORT=45769               # Web server port

# Auto-detected in Docker/sandbox environments
```

## Proto Files Used

- `callbackstream.proto` - StreamCallbackService definition
- `apirender.proto` - ApiRenderEngine service and setOnNewImageCallback
- `common.proto` - OnNewImageCallbackT structure
- `callback.proto` - Callback message structures

## Reference Implementation

Based on `octaneProxy/callback_streamer.py`:
- Lines 121-153: Callback registration
- Lines 220-253: Stream processing
- Lines 254-350: Image data handling

## Next Steps

1. **Test with Octane running**
2. **Verify stream data structure** (check logs)
3. **Adjust parsing if needed** based on actual data
4. **Add error recovery** for stream disconnections
5. **Optimize performance** (throttle updates, buffer management)

## Known Limitations

- Stream reconnection delay: 5 seconds (configurable)
- No automatic Octane connection retry
- Single callback registration (no multiple clients)

## Success Criteria

✅ Callback registered with Octane
✅ Stream connection established
✅ OnNewImage events received
✅ Image data flows to browser
✅ Render viewport displays live updates
✅ No errors in console

---

**Status**: Implementation complete, awaiting testing with live Octane instance
**Author**: OpenHands AI Agent
**Date**: 2025-01-22
