# Render Viewport Fix - Summary

## Problem
The render viewport in octaneWebR was not displaying images after updating to the latest Octane and SDK versions.

## Root Cause
By analyzing the C++ SDK example (`grpcSamples/sdk/grpc-api-examples/render-example/render-example.cpp`), I discovered that Octane's callback system works in **two separate steps**:

1. **OnNewImage Callback** (lines 271-282 in render-example.cpp)
   - This is a **notification only** - it signals that a new render is available
   - It does **NOT** contain the actual image data

2. **grabRenderResult()** (lines 275, 883-926 in render-example.cpp)
   - Must be called **after** receiving the OnNewImage callback
   - This fetches the actual render image buffer from Octane
   - Returns `ApiArrayApiRenderImage` with pixel data

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

## Solution Applied

**File**: `server/src/grpc/client.ts` (lines 360-396)

### Changes Made:
1. ✅ **Use proper callMethod() pattern** - Matches the pattern used throughout the codebase
2. ✅ **Promise-based error handling** - Cleaner async flow
3. ✅ **Case-sensitivity fallbacks** - Handle both `renderImages` and `renderimages` field names
4. ✅ **Enhanced logging** - Debug buffer size, type, and data structure

### Key Code Section:
```typescript
if (response.newImage) {
  console.log('🖼️  OnNewImage callback received (notification only)');
  
  // According to SDK examples: callbacks are notifications only!
  // We must call grabRenderResult() to fetch the actual image data
  this.callMethod('ApiRenderEngine', 'grabRenderResult', {})
    .then((grabResponse: any) => {
      if (!grabResponse || !grabResponse.result) {
        console.log('ℹ️  No render result available yet');
        return;
      }
      
      // Handle both camelCase and lowercase field names
      const renderImages = grabResponse.renderImages || grabResponse.renderimages;
      
      if (renderImages && renderImages.data && renderImages.data.length > 0) {
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

## Next Steps
If the viewport still doesn't work after this fix, check:
1. **Octane is rendering** - Verify in standalone Octane that rendering works
2. **gRPC connection** - Check that server can reach Octane on port 51022
3. **Console errors** - Look for gRPC errors or protobuf parsing issues
4. **Buffer encoding** - Verify buffer data is correctly encoded/decoded
5. **Octane version** - Ensure using latest Octane 2024+ with gRPC API support
