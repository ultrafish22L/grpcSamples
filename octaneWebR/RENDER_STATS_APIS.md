# Render Stats Bar - API Integration Guide

## Overview
This document details the Octane gRPC APIs needed to populate all fields in the render statistics bar.

---

## 📊 Scene Statistics APIs

### 1. Get Geometry Statistics
**Service:** `ApiRenderEngineService`  
**Method:** `getGeometryStatistics`  
**Proto File:** `apirender.proto`

**Request:**
```protobuf
message getGeometryStatisticsRequest {
  // No parameters required
}
```

**Response:**
```protobuf
message getGeometryStatisticsResponse {
  ApiGeometryStatistics stats = 1;
}

message ApiGeometryStatistics {
  uint32 triCount = 1;              // Triangle primitives
  uint32 dispTriCount = 2;          // Displacement triangles
  uint32 hairSegCount = 3;          // Hair segments
  uint64 voxelCount = 4;            // Volume voxels
  uint64 gaussianSplatCount = 5;    // Gaussian splats
  uint32 sphereCount = 6;           // Sphere primitives
  uint32 instanceCount = 7;         // Instances
  uint32 emitPriCount = 8;          // Emitter primitives
  uint32 emitInstanceCount = 9;     // Emitter instances
  uint32 analyticLiCount = 10;      // Analytic lights
}
```

**Usage:**
- **Total Primitives:** Sum of `triCount + dispTriCount + hairSegCount + sphereCount + emitPriCount`
- **Display Format:** `{totalPrimitives} pri` (e.g., "4032 pri")

---

### 2. Get Texture Statistics
**Service:** `ApiRenderEngineService`  
**Method:** `getTexturesStatistics`

**Response:**
```protobuf
message ApiTextureStatistics {
  uint32 usedRgba32Textures = 1;
  uint32 usedRgba64Textures = 2;
  uint32 usedY8Textures = 3;
  uint32 usedY16Textures = 4;
  uint32 usedVirtualTextures = 5;
}
```

**Usage:**
- Can be used for advanced stats or info panels

---

## 🖥️ Device/GPU APIs

### 3. Get Device Count
**Service:** `ApiRenderEngineService`  
**Method:** `getDeviceCount`

**Request:**
```protobuf
message getDeviceCountRequest {
  // No parameters
}
```

**Response:**
```protobuf
message getDeviceCountResponse {
  uint32 result = 1;  // Number of available devices
}
```

---

### 4. Get Device Name
**Service:** `ApiRenderEngineService`  
**Method:** `getDeviceName`

**Request:**
```protobuf
message getDeviceNameRequest {
  uint32 index = 1;  // Device index (0-based)
}
```

**Response:**
```protobuf
message getDeviceNameResponse {
  string result = 1;  // e.g., "NVIDIA GeForce RTX 4090"
}
```

**Usage:**
- Call with `index = 0` for primary GPU
- Display format: `{deviceName}` or `{deviceName} (RT)` if hardware RT is enabled

---

### 5. Check Hardware Ray Tracing
**Service:** `ApiRenderEngineService`  
**Method:** `deviceUsesHardwareRayTracing`

**Request:**
```protobuf
message deviceUsesHardwareRayTracingRequest {
  uint32 index = 1;  // Device index
}
```

**Response:**
```protobuf
message deviceUsesHardwareRayTracingResponse {
  bool result = 1;  // true if HW RT is enabled
}
```

**Usage:**
- If `result == true`, append " (RT)" to device name
- Example: "NVIDIA GeForce RTX 4090 (RT)"

---

### 6. Get Memory Usage
**Service:** `ApiRenderEngineService`  
**Method:** `getMemoryUsage`

**Request:**
```protobuf
message getMemoryUsageRequest {
  uint32 deviceIx = 1;  // Device index
}
```

**Response:**
```protobuf
message getMemoryUsageResponse {
  ApiDeviceMemoryUsage memUsage = 1;
}

message ApiDeviceMemoryUsage {
  uint64 usedDeviceMemory = 1;    // Bytes used
  uint64 freeDeviceMemory = 2;    // Bytes free
  uint64 totalDeviceMemory = 3;   // Total bytes
  uint64 outOfCoreMemory = 4;     // Out-of-core memory
  uint64 peerToPeerBytesUsed = 5; // P2P transfer bytes
}
```

**Usage:**
- Display format: `{totalDeviceMemory / (1024^3)} GB` (e.g., "24.0 GB")
- Can also show used/free for advanced UI

---

## 🔢 Version Info APIs

### 7. Get Octane Version String
**Service:** `ApiInfoService`  
**Method:** `octaneName`  
**Proto File:** `apiinfo.proto`

**Request:**
```protobuf
message octaneNameRequest {
  // No parameters
}
```

**Response:**
```protobuf
message octaneNameResponse {
  string result = 1;  // e.g., "Octane X 2023.1.0"
}
```

**Alternative Method:**
- `octaneVersion()` returns `int32` with encoded version number

**Usage:**
- Display format: `{major}:{minor}.{patch}.{build}`
- Example: "1:48.21.2"
- May need parsing if returned as full name string

---

## 📋 Integration Summary

### Stats Bar Left Side (Render Progress)
- Already implemented via `getRenderStatistics()`
- Fields: samples, time, speed, status

### Stats Bar Right Side (Scene/Device Info)

| Display | API Source | Format |
|---------|-----------|--------|
| **Primitives** | `getGeometryStatistics()` | `{sum} pri` |
| **Meshes** | TBD - Scene graph API | `{count} mesh` |
| **GPU Name** | `getDeviceName(0)` + `deviceUsesHardwareRayTracing(0)` | `{name} (RT)` |
| **Version** | `octaneName()` | `{version}` |
| **Memory** | `getMemoryUsage(0).totalDeviceMemory` | `{GB} GB` |

---

## 🔧 Implementation Plan

### Phase 1: Add gRPC Client Methods ✅
```typescript
// In server/src/grpc/client.ts
async getGeometryStatistics(): Promise<ApiGeometryStatistics>
async getDeviceName(index: number): Promise<string>
async getMemoryUsage(deviceIx: number): Promise<ApiDeviceMemoryUsage>
async deviceUsesHardwareRayTracing(index: number): Promise<boolean>
async getOctaneVersion(): Promise<string>
```

### Phase 2: WebSocket API Endpoints ✅
```typescript
// In server/src/api/routes.ts
router.get('/scene/geometry-stats', ...)
router.get('/device/info', ...)
router.get('/system/version', ...)
```

### Phase 3: React State & UI Updates ✅
```typescript
// In client/src/components/RenderToolbar/index.tsx
interface SystemInfo {
  primitiveCount: number;
  meshCount: number;
  gpuName: string;
  hasHardwareRT: boolean;
  totalMemoryGB: number;
  octaneVersion: string;
}
```

### Phase 4: Periodic Updates ✅
- Fetch geometry stats on scene load/change
- Cache device info (static data)
- Update on render start/stop

---

## 🎯 Display Format Reference

### Current Implementation (Octane Reference)
```
[Progress Bar] 1304/2720/5000 s/px, 695 Ms/sec, 00:00:02/00:00:03 (rendering...) | 4032 pri, 1 mesh, NVIDIA GeForce RTX 4090 (RT), 1:48.21.2/24.0 GB
```

### Field Sources
- `1304` → `beautySamplesPerPixel` (from `getRenderStatistics`)
- `2720` → `denoisedSamplesPerPixel` (from `getRenderStatistics`)
- `5000` → `beautyMaxSamplesPerPixel` (from `getRenderStatistics`)
- `695 Ms/sec` → `beautySamplesPerSecond / 1M` (from `getRenderStatistics`)
- `00:00:02` → `renderTime` (from `getRenderStatistics`)
- `00:00:03` → `estimatedRenderTime` (from `getRenderStatistics`)
- `4032 pri` → **`getGeometryStatistics()` (sum of counts)** ⭐
- `1 mesh` → TBD (scene graph API)
- `NVIDIA GeForce RTX 4090 (RT)` → **`getDeviceName(0)` + `deviceUsesHardwareRayTracing(0)`** ⭐
- `1:48.21.2` → **`octaneName()`** ⭐
- `24.0 GB` → **`getMemoryUsage(0).totalDeviceMemory`** ⭐

---

## 📝 Notes

### Proto File Locations
- **Render APIs:** `/server/proto/apirender.proto`
- **Info APIs:** `/server/proto/apiinfo.proto`

### Device Index
- Use `index = 0` for primary rendering device
- Multi-GPU support: loop through `getDeviceCount()` devices

### Mesh Count Source
- Not found in `ApiGeometryStatistics` or `RenderResultStatistics`
- Likely requires scene graph traversal or separate API
- May be in project manager or scene outliner APIs
- **TODO:** Investigate scene graph APIs for mesh/object count

### Version Format
- `octaneName()` returns full string (e.g., "Octane X 2023.1.0")
- May need regex parsing: `/(\d+):(\d+)\.(\d+)\.(\d+)/`
- Reference shows format: `1:48.21.2` (major:minor.patch.build)

### Memory Format
- API returns bytes as `uint64`
- Convert: `totalDeviceMemory / (1024 * 1024 * 1024)`
- Display: `{rounded} GB` (e.g., "24.0 GB")

### Primitive Count Calculation
```typescript
const totalPrimitives = 
  stats.triCount + 
  stats.dispTriCount + 
  stats.hairSegCount + 
  stats.sphereCount + 
  stats.emitPriCount;
```

---

## ✅ Status

- [x] Proto files analyzed
- [x] API methods identified
- [x] Message structures documented
- [ ] gRPC client methods added
- [ ] WebSocket endpoints created
- [ ] React UI integration
- [ ] Live testing with Octane instance
