# Render Viewport Fix - Summary

## Problem
The render viewport in octaneWebR was not displaying images after updating to the latest Octane and SDK versions.

## Root Cause
By analyzing both the **C++** (`render-example.cpp`) and **Python** (`render_example.py`) SDK examples, discovered that Octane's callback system can work in two modes:

### Understanding the Two Callback Modes

**Mode 1: Direct Image Data (Possibly Newer API)**
- Callback message includes `render_images` field with actual buffer data
- Can emit immediately without additional API call
- More efficient but may not be available in all Octane versions

**Mode 2: Notification-Only (SDK Examples Pattern)**
By analyzing the C++ and Python SDK examples, the callback system works in **two separate steps**:

1. **OnNewImage Callback**
   - C++: lines 271-282 in `render-example.cpp`
   - Python: lines 1084-1095 in `render_example.py` (`handle_event` function)
   - This is a **notification only** - it signals that a new render is available
   - It does **NOT** contain the actual image data

2. **grabRenderResult()**
   - C++: lines 275, 883-926 in `render-example.cpp`
   - Python: lines 1049-1071 in `render_example.py` (`grab_render_result` function)
   - Must be called **after** receiving the OnNewImage callback
   - This fetches the actual render image buffer from Octane
   - Returns `ApiArrayApiRenderImage` with pixel data (in `response.renderImages`)

## Bug Details
In `server/src/grpc/client.ts` (line 345-374), the code was attempting to call `grabRenderResult()` but had two issues:

### Issue 1: Incorrect Calling Pattern
```typescript
// ❌ WRONG - Direct service method call with callback
const renderEngine = this.getService('ApiRenderEngineService');
renderEngine.grabRenderResult(grabRequest, (error, grabResponse) => { ... });
```

```typescript
// ✅ CORRECT - Use the callMethod() helper (promise-based)
this.callMethod('ApiRenderEngine', 'grabRenderResult', {})
  .then((grabResponse) => { ... })
  .catch((error) => { ... });
```

### Issue 2: Limited Error Handling
- No case-sensitivity fallbacks for proto field names
- Limited logging for debugging buffer data issues

### Issue 3: Always Calling grabRenderResult()
- Original code always called `grabRenderResult()` even if callback contained image data
- This is inefficient and may fail if render engine doesn't have separate result buffer

## Key Insight from Python SDK Example

The **Python example** (`render_example.py`) revealed important differences:

1. **No explicit callback registration** (lines 1142-1143, 1108-1118)
   - Python code doesn't call `setOnNewImageCallback()`
   - Just subscribes to `callbackChannel` stream directly
   - Callbacks arrive automatically

2. **Simple stream subscription** (lines 1115-1118)
   ```python
   stub = callbackstream_pb2_grpc.StreamCallbackServiceStub(channel)
   for req in stub.callbackChannel(empty_pb2.Empty()):
       handle_event(req)
   ```

3. **Always calls grabRenderResult()** (lines 1087-1092)
   - Callback is treated as notification-only
   - Always fetches data via `grab_render_result(global_channel)`
   - No check for data in callback itself

This suggests callback registration via `setOnNewImageCallback()` is **optional** and the stream works regardless.

## Solution Applied

**File**: `server/src/grpc/client.ts` (lines 360-396)

### Changes Made (Latest - Commit 74ed51ae):

1. ✅ **Smart callback data detection** - Check for image data in callback FIRST
   - Priority 1: `response.render_images` (root level)
   - Priority 2: `response.newImage.render_images` (nested in callback)
   - Priority 3: `response.renderimages` (lowercase variant)
   - Fallback: Call `grabRenderResult()` only if no data present

2. ✅ **Optional callback registration** - Following Python SDK pattern
   - `setOnNewImageCallback()` wrapped in try-catch
   - Registration failure doesn't stop stream
   - Callbacks work via `callbackChannel` regardless

3. ✅ **Use proper callMethod() pattern** - Matches the pattern used throughout the codebase

4. ✅ **Promise-based error handling** - Cleaner async flow

5. ✅ **Improved logging** - Distinguish different failure modes:
   - `result=false` (render initializing, normal)
   - `result=true` but 0 images (unexpected)
   - null/undefined response (critical error)
   - Show where image data was found (callback vs grab)

### Key Code Section:
```typescript
// Step 1: Check for image data in callback FIRST (multiple possible locations)
let renderImages = null;
let imageSource = '';

if (response.render_images?.data?.length > 0) {
  renderImages = response.render_images;
  imageSource = 'root level';
} else if (response.newImage?.render_images?.data?.length > 0) {
  renderImages = response.newImage.render_images;
  imageSource = 'newImage callback';
} else if (response.renderimages?.data?.length > 0) {
  renderImages = response.renderimages;
  imageSource = 'root level (lowercase)';
}

// Step 2: If we found image data, emit directly
if (renderImages) {
  console.log(`✅ Found render images in callback (${imageSource})`);
  this.emit('OnNewImage', { render_images: renderImages, ... });
}
// Step 3: Otherwise fall back to grabRenderResult()
else if (response.newImage) {
  console.log('🖼️  OnNewImage callback without data - calling grabRenderResult()');
  
  this.callMethod('ApiRenderEngine', 'grabRenderResult', {})
    .then((grabResponse: any) => {
      if (!grabResponse) {
        console.warn('⚠️  grabRenderResult returned null/undefined');
        return;
      }
      if (grabResponse.result === false) {
        console.log('ℹ️  No render result (result=false) - initializing');
        return;
      }
      
      const grabbedImages = grabResponse.renderImages || grabResponse.renderimages;
      if (grabbedImages?.data?.length > 0) {
        this.emit('OnNewImage', {
          render_images: renderImages,
          callback_id: response.newImage?.callback_id,
          user_data: response.newImage?.user_data
        });
      }
    })
    .catch((error: any) => {
      console.error('❌ grabRenderResult failed:', error.message);
    });
}
```

## Testing Instructions

### Prerequisites
1. Octane Render installed and running on localhost:51022 (or host.docker.internal:51022)
2. A scene loaded in Octane (any scene with renderable objects)

### Test Steps
1. **Start octaneWebR**:
   ```bash
   cd /workspace/project/grpcSamples/octaneWebR
   npm install  # If not already done
   npm run dev  # Starts on port 58407
   ```

2. **Connect to Octane**:
   - Open http://localhost:58407 in browser
   - Click "Connect to Octane" button
   - Should see "Connected" status

3. **Start Rendering**:
   - In the Render Viewport panel, click the "Play" button (or use Render menu)
   - Watch the browser console for these log messages:

   **Expected Console Output** (Success):
   ```
   📡 Starting callback streaming...
   ✅ Callback registered
   🖼️  OnNewImage callback received (notification only)
   📤 gRPC call: ApiRenderEngine.grabRenderResult
   ✅ ApiRenderEngine.grabRenderResult success
   ✅ Got render images from grabRenderResult: {
     count: 1,
     firstImageSize: { x: 1920, y: 1080 },
     firstImageType: "IMAGE_TYPE_LDR_RGBA",
     firstImageBufferSize: 2073600,
     firstImageBufferDataType: "object",
     firstImageBufferDataLength: 2073600
   }
   📸 [CallbackManager] Received 1 render image(s)
   ```

4. **Verify Viewport**:
   - The render should appear in the viewport canvas
   - Image should update in real-time as rendering progresses
   - Status bar should show resolution, buffer size, and samples per pixel

### What to Look For

#### ✅ Success Indicators:
- Console shows "✅ Got render images from grabRenderResult"
- Viewport displays the rendered image
- Image updates progressively as samples accumulate
- No error messages in console

#### ❌ Failure Indicators:
- Console shows "❌ grabRenderResult failed"
- Console shows "⚠️  grabRenderResult returned no images"
- Viewport remains blank or shows placeholder
- Error: "Method grabRenderResult not found"

## Technical Details

### Proto Structure
From `server/proto/apirender.proto`:

```protobuf
message grabRenderResultResponse {
    bool result = 1;  // TRUE if render results available
    ApiArrayApiRenderImage renderImages = 2;  // Array of render images
}

message ApiRenderImage {
    ImageType type = 1;                    // LDR_RGBA, HDR_RGBA, etc.
    uint32_2 size = 5;                     // {x: width, y: height}
    uint32 pitch = 6;                      // Pixels per row
    Buffer buffer = 7;                     // Raw pixel data
    float tonemappedSamplesPerPixel = 9;   // Current samples
    float renderTime = 14;                 // Render time in seconds
}

message Buffer {
    bytes data = 1;   // Raw binary pixel data
    uint32 size = 2;  // Buffer size in bytes
}
```

### Image Data Flow
1. **Octane** → gRPC `callbackChannel` stream → **OnNewImage notification**
2. **octaneWebR** → gRPC `grabRenderResult()` call → **Fetch image data**
3. **Server** → WebSocket → **Client** (buffer as JSON-serialized Buffer)
4. **Client** → Canvas → **Display rendered image**

### Buffer Encoding
- gRPC sends `bytes` as Node.js Buffer objects
- WebSocket JSON serializes Buffer as: `{type: "Buffer", data: [bytes]}`
- Client-side `displayCallbackImage()` handles both base64 and Buffer formats

## Reference Files
- **C++ Example**: `grpcSamples/sdk/grpc-api-examples/render-example/render-example.cpp`
  - Line 271-282: OnNewImage callback handler
  - Line 883-926: grabRenderResult() implementation
  - Line 836-880: Buffer conversion logic
  
- **Proto Definition**: `server/proto/apirender.proto`
  - grabRenderResultRequest / Response messages
  - ApiRenderImage structure
  
- **Octane SE Manual**: https://docs.otoy.com/standaloneSE/
  - Reference UI for expected viewport behavior

## Commit
```
commit 6d0875b2
Author: [Your Name]
Date:   2025-01-28

Fix: Render viewport grabRenderResult() call pattern

Fixes render viewport not displaying images after Octane/SDK update.
```

## Debugging: When grabRenderResult() Returns 0 Images

If you see "⚠️  grabRenderResult returned 0 images", check the console output carefully:

### Case 1: `result=false` (Normal Early State)
```
ℹ️  No render result available (result=false) - render may be initializing
```
**Meaning**: Render engine hasn't produced a frame yet
**Action**: Wait for more callbacks - this is normal at render start

### Case 2: `result=true` but 0 images (Unexpected)
```
⚠️  grabRenderResult returned 0 images (result=true but no data): {
  result: true,
  hasRenderImages: true,
  dataLength: 0
}
```
**Meaning**: API says data is available but array is empty
**Action**: Check if:
- Callback might contain data directly (should be detected by priority checks)
- Octane version has different API behavior
- Check console for "✅ Found render images in callback" message

### Case 3: Image Data in Callback (Efficient Path)
```
✅ [Stream] Found render images in callback (root level): { count: 1, ... }
```
**Meaning**: Callback included image data directly - no `grabRenderResult()` needed
**Action**: This is the optimal path! No additional action needed.

## Next Steps
If the viewport still doesn't work after this fix, check:
1. **Console logs** - Look for which path is being taken (callback vs grab)
2. **Octane is rendering** - Verify in standalone Octane that rendering works
3. **gRPC connection** - Check that server can reach Octane on port 51022
4. **Console errors** - Look for gRPC errors or protobuf parsing issues
5. **Buffer encoding** - Verify buffer data is correctly encoded/decoded
6. **Octane version** - Ensure using latest Octane 2024+ with gRPC API support
7. **Callback registration** - Check if registration succeeded or was skipped (both should work)
