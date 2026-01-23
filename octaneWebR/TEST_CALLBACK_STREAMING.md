# Testing Callback Streaming Fix

This guide walks through testing the callback streaming fix for the render viewport.

## Prerequisites

1. **Octane Render** running with:
   - gRPC server enabled at `127.0.0.1:51022` (or `localhost:51022`)
   - LiveLink enabled
   - A scene loaded (any scene)

2. **Project built**:
   ```bash
   cd /workspace/project/grpcSamples/octaneWebR
   npm install
   npm run build
   ```

## Testing Steps

### 1. Start the Server

In terminal window 1:

```bash
cd /workspace/project/grpcSamples/octaneWebR
npm start
```

**Expected Output:**
```
╔═══════════════════════════════════════════════════╗
║           OctaneWebR Server Started               ║
╠═══════════════════════════════════════════════════╣
║  HTTP Server:     http://localhost:45769          ║
║  WebSocket:       ws://localhost:45769/api/callbacks  ║
║  Octane gRPC:     localhost:51022                 ║
╚═══════════════════════════════════════════════════╝

📡 gRPC channel initialized: localhost:51022
✅ Core proto definitions loaded successfully
✅ gRPC client initialized successfully
📡 WebSocket server initialized at /api/callbacks
✅ WebSocket callback streaming ready
🎬 Starting callback streaming...
📝 Registering OnNewImage callback...
✅ Callback registered: { callbackId: ... }
📡 Starting callback channel stream...
✅ Found service: StreamCallbackService at octaneapi.StreamCallbackService
✅ Created StreamCallbackService client instance
✅ Callback streaming started
✅ Octane callback streaming initialized
```

**Troubleshooting Server Start:**

If you see errors:

- **"Connection timeout"** → Octane not running or gRPC server not enabled
- **"ECONNREFUSED"** → Check Octane gRPC address (should be 127.0.0.1:51022)
- **"Proto file not found"** → Run `npm run generate:proto` first

### 2. Open Browser

Open browser to: **http://localhost:45769**

**Expected in Browser Console:**
```
🎯 useOctane: Setting up event listeners
🎬 OctaneClient initialized: http://localhost:45769
✅ WebSocket connected
🎯 useOctane: handleConnected called
📸 [CallbackViewport] Initializing...
✅ Render viewport initialized
```

### 3. Trigger Render Update

In Octane:
- Move camera
- Change material
- Add/remove objects
- Or just wait if auto-render is enabled

### 4. Watch Server Logs

**Expected when render updates:**
```
📥 [Stream] Received callback data: {
  hasResponse: true,
  responseType: 'object',
  keys: [...],
  hasNewImage: true,
  ...
}
📥 [Stream] newImage payload: {
  type: 'object',
  keys: [...],
  userData: 0,
  hasRenderImages: true,
  hasCallbackId: true
}
✅ [Stream] Found render_images in newImage, emitting OnNewImage event
📸 [CallbackManager] Received 1 render image(s)
📸 [CallbackManager] Image details: {
  type: 0,
  size: { x: 800, y: 600 },
  bufferSize: 1920000,
  hasData: true
}
📡 [WebSocket] Forwarding OnNewImage to client
```

### 5. Watch Browser Console

**Expected:**
```
📸 [CallbackViewport] Received 1 render image(s)
📸 [CallbackViewport] Image details: { type: 0, size: {...}, ... }
✅ [CallbackViewport] Image displayed successfully
```

### 6. Verify Render Display

In the browser:
- [ ] Render viewport shows the image
- [ ] Image matches what you see in Octane
- [ ] Frame count increments with each update
- [ ] Status bar shows resolution, file size, samples per pixel

## Debug Mode

If images are not appearing, enable debug mode:

### Server Debug Logs

The server already has detailed logging enabled in the stream handler.
Watch for:

1. **Registration**:
   ```
   ✅ Callback registered: { ... }
   ```

2. **Stream Data**:
   ```
   📥 [Stream] Received callback data: { ... }
   ```

3. **Image Data**:
   ```
   📸 [CallbackManager] Received N render image(s)
   ```

### Browser Debug

Open DevTools Console and check:

1. **WebSocket**:
   ```
   ✅ WebSocket connected
   ```

2. **Callbacks**:
   ```
   📸 [CallbackViewport] Received image data
   ```

3. **Errors**:
   Look for `❌` or `⚠️` messages

## Common Issues

### Issue 1: "Callback registration failed"

**Cause**: Octane not running or LiveLink not enabled

**Fix**:
1. Start Octane
2. Enable LiveLink: Settings → LiveLink → Enable
3. Restart server

### Issue 2: "Stream connection failed"

**Cause**: Proto file mismatch or service not available

**Fix**:
1. Check Octane version (should support gRPC streaming)
2. Regenerate protos: `npm run generate:proto`
3. Restart server

### Issue 3: "No image data in callback"

**Cause**: Stream receiving data but wrong structure

**Fix**:
1. Check server logs for actual data structure
2. Look for `📥 [Stream] newImage payload:` log
3. Compare structure with expected in CALLBACK_STREAMING_FIX.md
4. Adjust parsing logic if needed

### Issue 4: "WebSocket disconnected"

**Cause**: Server crashed or network issue

**Fix**:
1. Check server terminal for errors
2. Restart server
3. Refresh browser

### Issue 5: "Image appears garbled"

**Cause**: Buffer conversion issue

**Fix**:
1. Check image type (LDR vs HDR)
2. Verify buffer encoding (base64 vs Buffer object)
3. Check pitch and size values

## Performance Testing

### Test Render Speed

1. Enable auto-render in Octane
2. Move camera continuously
3. Watch frame count in browser
4. Check CPU/memory usage

**Expected**:
- Updates should be smooth (< 100ms latency)
- No memory leaks (stable memory usage)
- No dropped frames (all updates received)

### Test Multiple Clients

1. Open browser in multiple tabs
2. All should receive same updates
3. No conflicts or race conditions

## Stress Testing

### Test Long Running

1. Start server
2. Leave running for extended period (1+ hours)
3. Verify stream stays connected
4. No memory leaks

### Test Reconnection

1. Stop Octane
2. Server should log stream error
3. Start Octane
4. Server should reconnect automatically

## Success Criteria

✅ **All checks passed:**
- [x] Server starts without errors
- [x] Callback registered successfully
- [x] Stream connected and receiving data
- [x] WebSocket forwarding to browser
- [x] Browser receiving and displaying images
- [x] Real-time updates working
- [x] No errors in console
- [x] Stable performance over time

## Data Structure Reference

### Expected Stream Response

```typescript
{
  newImage: {
    user_data: 0,
    callback_id: 1,
    render_images: {
      data: [
        {
          type: 0,  // 0 = LDR, 1 = HDR
          size: { x: 800, y: 600 },
          pitch: 3200,  // bytes per row
          buffer: {
            data: "base64EncodedImageData...",
            size: 1920000,
            encoding: "base64"
          },
          tonemappedSamplesPerPixel: 100.5,
          renderTime: 2.34,
          // ... other fields
        }
      ]
    }
  }
}
```

### WebSocket Message Format

```json
{
  "type": "newImage",
  "data": {
    "render_images": { ... },
    "callback_id": 1,
    "timestamp": 1705936284531
  }
}
```

## Next Steps

Once testing is complete:
1. Document any data structure differences found
2. Update parsing logic if needed
3. Add unit tests for buffer conversion
4. Optimize performance (throttling, buffering)
5. Add error recovery mechanisms

## Support

If issues persist:
1. Check CALLBACK_STREAMING_FIX.md for architecture details
2. Review server logs for detailed stream data
3. Compare with Python reference implementation (octaneProxy)
4. Check Octane version compatibility

---

**Last Updated**: 2025-01-22
**Status**: Ready for testing
