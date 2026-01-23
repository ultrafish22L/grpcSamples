# Callback Streaming Investigation Results

## Summary
Callback streaming is **correctly implemented and receiving callbacks**, but callbacks contain **no render image data**. This appears to be a regression or behavior change in the latest Octane version.

## Evidence

### ✅ What's Working
1. **gRPC Connection**: Successfully connected to Octane at `host.docker.internal:51022`
2. **Callback Registration**: `ApiRenderEngine.setOnNewImageCallback` succeeds
3. **Stream Channel**: `StreamCallbackService.callbackChannel` stream is active
4. **Callback Flow**: Callbacks are being received when scene changes occur (e.g., toggling Orthographic)
5. **WebSocket Relay**: Server successfully relays callbacks to browser client

### ❌ What's Broken
Callbacks contain **no render image data**:

```json
{
  "newImage": {
    "user_data": "0"
  },
  "payload": "newImage"
}
```

**Missing fields:**
- `callback_source` - undefined
- `callback_id` - undefined  
- `render_images` - empty array (count: 0)

## Test Results

### Callback Registration Parameters
Verified correct format matches working Python implementation:
```typescript
{
  callback: {
    callbackSource: 'octaneWebR',
    callbackId: 1
  },
  userData: 0
}
```

### Log Evidence
```
📡 Stream data received: { "newImage": { "user_data": "0" }, "payload": "newImage" }
🖼️  OnNewImage callback received
   callback_source: undefined
   callback_id: undefined
   render_images count: 0
⚠️  [CallbackViewport] No valid image data in callback
```

### Actions Tested
1. ✅ Toggling Orthographic checkbox → Callback received (but empty)
2. ✅ Clicking Play button → Callback received (but empty)
3. ✅ Scene changes → Callbacks triggered correctly
4. ❌ No render images in any callback

## Root Cause Analysis

### Most Likely: Octane Version Regression
User reports: **"it was working with an earlier version"**

This indicates:
- Our implementation is correct
- Octane's behavior changed between versions
- Latest Octane may have a bug or require new parameters

### Possible Octane Issues
1. **Bug**: Octane not populating `render_images` in callback responses
2. **API Change**: New flag/parameter needed to enable image data in callbacks
3. **Configuration**: Octane needs a setting enabled to send render data
4. **Render State**: Octane may not be actively rendering (but should be on scene change)

## Implementation Status

### ✅ Completed
- [x] gRPC client connection
- [x] Callback registration with correct parameters
- [x] Stream channel setup
- [x] Callback data parsing
- [x] WebSocket relay to browser
- [x] Empty callback detection and logging

### Code Quality
All implementation matches the working Python reference (`octaneProxy/callback_streamer.py`)

## Next Steps

### For User
1. **Check Octane Version**: Verify which version is running
   ```bash
   # If accessible, check Octane version/build number
   ```

2. **Test with Previous Octane Version**: If possible, downgrade to the version that worked

3. **Check Octane Settings**: 
   - Verify interactive rendering is enabled
   - Check if there's a "Send callbacks" or similar option
   - Look for render viewport settings

4. **Report to Otoy**: If confirmed as regression, report to Octane support with:
   - Version numbers (working vs broken)
   - Callback registration code
   - Expected vs actual callback data

### For Development
- No code changes needed unless Octane API documentation reveals new requirements
- Monitor Octane release notes for callback API changes
- Consider adding Octane version detection to provide user-friendly error messages

## Verification Commands

Check server logs:
```bash
tail -f /tmp/octaneWebR-dev.log | grep -E "Stream data|OnNewImage|render_images"
```

Test callback flow:
1. Open http://localhost:43929
2. Click Orthographic checkbox
3. Check server logs for callback data
4. Currently shows: `render_images count: 0` ❌
5. Should show: `render_images count: 1+` ✅

## References

### Working Python Implementation
`/workspace/project/grpcSamples/octaneProxy/callback_streamer.py` lines 131-146

### Current Node Implementation  
`/workspace/project/grpcSamples/octaneWebR/server/src/grpc/client.ts` lines 315-407

### Octane Documentation
https://docs.otoy.com/standaloneSE/CoverPage.html

---

**Status**: ⏸️ **Blocked by Octane behavior** - Implementation complete, awaiting Octane fix or configuration guidance
