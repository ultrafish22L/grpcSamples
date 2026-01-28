# Statistics Callback Analysis

## Discovery

**Key Finding:** The `OnStatisticsData` callback from `callbackstream.proto` does **NOT** contain render statistics data directly.

### Proto Definition

```protobuf
message OnStatisticsData
{
    uint64 user_data = 1;  // ONLY contains user_data, no statistics!
}
```

This is just a **notification/trigger** callback, not a data payload callback.

---

## How Statistics Actually Work

### 1. Callback as Trigger
When Octane has new render statistics available, it sends `OnStatisticsData` via the callback stream.

**What it contains:**
- `user_data` - Optional user context data (uint64)

**What it does NOT contain:**
- ❌ Samples per pixel
- ❌ Render time
- ❌ Sample rate
- ❌ Resolution
- ❌ GPU info
- ❌ Any actual statistics data

### 2. Fetch Statistics via API
After receiving the `OnStatisticsData` notification, we must call `getRenderStatistics()` to fetch the actual data.

**API Call:**
```typescript
callMethod('ApiRenderEngine', 'getRenderStatistics', {})
```

**Returns:** `RenderResultStatistics` (see `octanerenderpasses.proto`)

---

## RenderResultStatistics Structure

From `octanerenderpasses.proto`, the full statistics object contains:

```protobuf
message RenderResultStatistics {
    uint32_2 setSize = 1;                    // Resolution settings
    uint32_2 usedSize = 2;                   // Actual used size
    SubSampleMode subSampleMode = 3;
    float upSamplingRatio = 4;
    TonemapBufferType bufferType = 5;
    NamedColorSpace colorSpace = 6;
    bool isLinear = 7;
    bool hasAlpha = 8;
    PremultipliedAlphaType premultipliedAlphaType = 9;
    bool keepEnvironment = 10;
    CLevelT changeLevel = 11;
    bool hasPendingUpdates = 12;
    uint32 deepBinCount = 13;
    uint32 deepSeedSpp = 14;
    uint32 cryptomatteSeedSpp = 15;
    bool deepPassesEnabled = 16;
    uint32 tonemapPassesCount = 17;
    ApiArrayRenderPassId tonemapPasses = 18;
    uint32 passesCount = 19;
    ApiArrayRenderPassId renderPasses = 20;
    uint32 beautyWipeCount = 21;
    
    uint32 beautySamplesPerPixel = 22;       // ⭐ Samples displayed
    uint32 beautyMaxSamplesPerPixel = 23;    // ⭐ Max samples limit
    double beautySamplesPerSecond = 24;      // ⭐ Render speed (sps)
    
    uint32 regionSamplesPerPixel = 25;
    uint32 denoisedSamplesPerPixel = 26;
    uint32 regionDenoisedSamplesPerPixel = 27;
    uint32 infoWipeCount = 28;
    uint32 infoSamplesPerPixel = 29;
    uint32 infoMaxSamplesPerPixel = 30;
    double infoSamplesPerSecond = 31;
    
    RenderState state = 32;                  // ⭐ Render status
    double renderTime = 33;                  // ⭐ Total render time
    double estimatedRenderTime = 34;
}
```

---

## Current Implementation Flow

### 1. Callback Received (grpc/client.ts)
```typescript
if (response.newStatistics) {
  console.log('📊 OnStatisticsData callback received:', 
    JSON.stringify(response.newStatistics, null, 2));
  
  // Response only contains: { user_data: <uint64> }
}
```

### 2. Fetch Full Statistics (grpc/client.ts)
```typescript
this.callMethod('ApiRenderEngine', 'getRenderStatistics', {})
  .then((statsResponse: any) => {
    console.log('✅ Got render statistics (FULL RESPONSE):', 
      JSON.stringify(statsResponse.statistics, null, 2));
    
    // statsResponse.statistics = RenderResultStatistics object
  });
```

### 3. Forward to CallbackManager (services/callbackManager.ts)
```typescript
console.log('📊 [CallbackManager] Received render statistics (FULL DATA):', 
  JSON.stringify(data, null, 2));
```

### 4. Forward to WebSocket Client (api/websocket.ts)
```typescript
console.log('📊 [WebSocket] Forwarding OnNewStatistics to client (FULL DATA):', 
  JSON.stringify(data, null, 2));
```

---

## Logging Added

### Purpose
Verify what data is actually returned by `getRenderStatistics()` at each stage of the pipeline.

### What Will Be Logged
1. **OnStatisticsData callback payload** (just user_data)
2. **Full RenderResultStatistics response** from API call
3. **Data forwarded through CallbackManager**
4. **Data sent to WebSocket client**

All logs use `JSON.stringify(data, null, 2)` for complete visibility.

---

## Render Stats Bar Data Mapping

Based on `RenderResultStatistics`, here's how we populate the stats bar:

| UI Display | RenderResultStatistics Field |
|------------|------------------------------|
| `1.0 spp` | `beautySamplesPerPixel` |
| `00:00:12` | `renderTime` (converted to HH:MM:SS) |
| `(rendering)` | `state` (RenderState enum) |
| `1 mesh` | *(from scene API, not in statistics)* |
| `NVIDIA GeForce RTX 4090 (RT)` | *(from device info API)* |
| `1:48.21.2` | *(Octane version string)* |
| `24.0 GB` | *(GPU memory from device API)* |

### Note
Some stats bar data comes from **other APIs**, not from RenderResultStatistics:
- Mesh count: Scene/geometry APIs
- GPU name/memory: Device info APIs
- Octane version: System info API

---

## Testing Recommendations

### 1. Start Dev Server & Monitor Logs
```bash
npm run dev
```

### 2. Trigger Render Statistics Updates
- Mouse drag in render viewport (triggers continuous rendering)
- Watch console for statistics callbacks (~1 second intervals)

### 3. Verify Logged Data
Check that `getRenderStatistics()` returns:
- ✅ `beautySamplesPerPixel` - Current samples
- ✅ `renderTime` - Elapsed time
- ✅ `state` - Render status
- ✅ `beautySamplesPerSecond` - If available
- ✅ `beautyMaxSamplesPerPixel` - Sample limit

### 4. Check for Missing Data
If certain fields are always `0` or `undefined`:
- May need different API call
- May need scene to be fully loaded
- May require specific render settings

---

## Summary

**Correct Understanding:**
- `OnStatisticsData` = Notification trigger (no data)
- `getRenderStatistics()` = Fetch actual data
- `RenderResultStatistics` = Full statistics object

**This pattern matches Octane's design:**
- Callback stream = lightweight notifications
- API calls = fetch full data on demand
- Reduces bandwidth for high-frequency updates

**Next Steps:**
1. Test with dev server running
2. Review full logged statistics data
3. Verify all needed fields are available
4. Update stats bar mapping if needed
