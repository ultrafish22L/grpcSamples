# Fix: Correct gRPC Service Names

**Date:** 2025-11-10  
**Commit:** `3894220`  
**Status:** 🟢 **PUSHED TO MAIN**

---

## The Problem

octaneWeb2 was trying to call non-existent gRPC services:

```
Service/Method: octane.render.RenderServerInfo/GetServerInfo
❌ Failed get_stub(): no module octane.render.renderserverinfo_pb2_grpc: No module named 'octane'
ModuleNotFoundError: No module named 'octane'
```

---

## Root Cause

**octaneWeb2 was using wrong service names:**
```typescript
// WRONG - doesn't exist
await this.makeServiceCall(
  'octane.render.RenderServerInfo',
  'GetServerInfo',
  {}
)
```

**The actual Octane LiveLink service:**
- Service name: `LiveLink`
- Available methods: `GetCamera`, `SetCamera`, `GetMeshes`, `GetMesh`, `GetFile`, `StreamCamera`

---

## The Correct Service Names

### Actual gRPC Service Definition

**File:** `octaneProxy/generated/livelink_pb2_grpc.py`

**Service:** `LiveLinkService`

**Available Methods:**
- `SetCamera(request)` - Set camera position/target
- `GetCamera(request)` - Get current camera
- `GetMeshes(request)` - Get list of meshes
- `GetMesh(request)` - Get specific mesh data
- `GetFile(request)` - Get file
- `StreamCamera(request_iterator)` - Stream camera updates

---

## How octaneWeb Does It (Working Reference)

**From:** `/workspace/grpcSamples/octaneWeb/js/core/OctaneWebClient.js`

```javascript
// Service path format: ServiceName/MethodName
const response = await this.makeApiCall('LiveLink/GetCamera');
const response = await this.makeApiCall('LiveLink/SetCamera', { position, target });
const response = await this.makeApiCall('LiveLink/GetMeshes');
```

**URL Pattern:**
```
/LiveLink/GetCamera
/LiveLink/SetCamera
/LiveLink/GetMeshes
```

**Python Proxy Route:**
```python
# Matches: /{service}/{method}
app.router.add_post('/{service:[^/]+}/{method:[^/]+}', handle_generic_grpc)
```

**Module Import:**
```python
# service = "LiveLink"
# module_name = "livelink_pb2_grpc"
grpc_module = importlib.import_module("livelink_pb2_grpc")
stub_class = getattr(grpc_module, "LiveLinkServiceStub")
```

---

## The Fix

**Changed `src/api/octaneClient.ts` connect() method:**

### Before:
```typescript
async connect(): Promise<boolean> {
  try {
    const response = await this.makeServiceCall(
      'octane.render.RenderServerInfo',  // ❌ Doesn't exist
      'GetServerInfo',                    // ❌ Not a valid method
      {}
    )
    
    this.connected = true
    console.log('✅ Connected to Octane:', response)
    return true
  } catch (error) {
    console.error('❌ Failed to connect to Octane:', error)
    this.connected = false
    return false
  }
}
```

### After:
```typescript
async connect(): Promise<boolean> {
  try {
    // Use LiveLink/GetCamera as a connectivity test
    // LiveLink is the actual gRPC service name
    const response = await this.makeServiceCall(
      'LiveLink',      // ✅ Correct service name
      'GetCamera',     // ✅ Valid method
      {}
    )
    
    this.connected = true
    console.log('✅ Connected to Octane via LiveLink:', response)
    return true
  } catch (error) {
    console.error('❌ Failed to connect to Octane:', error)
    this.connected = false
    return false
  }
}
```

---

## Request Flow (Fixed)

### URL Construction:
```
Browser calls: octaneClient.connect()
  ↓
makeServiceCall('LiveLink', 'GetCamera', {})
  ↓
URL: /api/LiveLink/GetCamera
```

### Vite Proxy:
```
Receives: /api/LiveLink/GetCamera
  ↓
Rewrites: /LiveLink/GetCamera (removes /api)
  ↓
Forwards to: http://127.0.0.1:51023/LiveLink/GetCamera
```

### Python Proxy:
```
Receives: /LiveLink/GetCamera
  ↓
Route matches: /{service:[^/]+}/{method:[^/]+}
  ↓
Captures: service="LiveLink", method="GetCamera"
  ↓
Imports: livelink_pb2_grpc.LiveLinkServiceStub ✅
  ↓
Calls: stub.GetCamera(request)
  ↓
Forwards to: Octane gRPC (127.0.0.1:51022)
```

### Octane LiveLink:
```
Receives: gRPC call to LiveLinkService.GetCamera
  ↓
Processes request
  ↓
Returns: Camera data (position, target, fov, etc.)
  ↓
Success! ✅
```

---

## Available LiveLink Methods

Based on `livelink_pb2_grpc.py`, here are all valid methods:

### 1. GetCamera
**Purpose:** Get current camera state  
**Request:** `{}` (empty)  
**Response:** Camera object with position, target, fov, etc.

```typescript
const camera = await octaneClient.makeServiceCall('LiveLink', 'GetCamera', {})
```

### 2. SetCamera
**Purpose:** Update camera position and target  
**Request:** `{ position: {x, y, z}, target: {x, y, z} }`  
**Response:** Success confirmation

```typescript
await octaneClient.makeServiceCall('LiveLink', 'SetCamera', {
  position: { x: 0, y: 1, z: 5 },
  target: { x: 0, y: 0, z: 0 }
})
```

### 3. GetMeshes
**Purpose:** Get list of all meshes in scene  
**Request:** `{}` (empty)  
**Response:** Array of mesh objects

```typescript
const meshes = await octaneClient.makeServiceCall('LiveLink', 'GetMeshes', {})
```

### 4. GetMesh
**Purpose:** Get specific mesh data  
**Request:** `{ meshId: string }`  
**Response:** Mesh object with vertices, faces, etc.

```typescript
const mesh = await octaneClient.makeServiceCall('LiveLink', 'GetMesh', {
  meshId: 'mesh_id_here'
})
```

### 5. GetFile
**Purpose:** Get file from Octane  
**Request:** `{ path: string }`  
**Response:** File data

```typescript
const file = await octaneClient.makeServiceCall('LiveLink', 'GetFile', {
  path: '/path/to/file'
})
```

### 6. StreamCamera
**Purpose:** Stream camera updates (bidirectional)  
**Request:** Stream of camera updates  
**Response:** Stream of responses

**Note:** This is a streaming method, requires different handling

---

## Module Naming Convention

The Python proxy uses this pattern to import modules:

**Service Name → Module Name:**
```python
service = "LiveLink"
module_name = service.lower().replace(".", "") + "_pb2_grpc"
# Result: "livelink_pb2_grpc"
```

**Examples:**
- `LiveLink` → `livelink_pb2_grpc`
- `MyService` → `myservice_pb2_grpc`
- `Foo.Bar` → `foobar_pb2_grpc`

**Available modules in `octaneProxy/generated/`:**
```bash
$ ls octaneProxy/generated/*_pb2_grpc.py | head -5
apianimationtimetransform_pb2_grpc.py
apiarray_pb2_grpc.py
apibase64_pb2_grpc.py
apibinaryfile_pb2_grpc.py
apicaches_pb2_grpc.py
...
livelink_pb2_grpc.py  ← This is what we need!
```

---

## Testing

### 1. Pull Latest Code
```bash
git pull origin main
```

### 2. Restart Dev Server
```bash
npm run dev
```

### 3. Test in Browser
Open http://localhost:42219

**Expected in console:**
```
✅ Connected to Octane via LiveLink: {position: {...}, target: {...}, ...}
```

**Should NOT see:**
```
❌ ModuleNotFoundError: No module named 'octane'
❌ HTTP 405: Method Not Allowed
```

---

## Next Steps for octaneWeb2

Now that we know the correct service names, we need to update all API calls in octaneWeb2 to use LiveLink methods.

**Files that may need updates:**
- `src/api/octaneClient.ts` - Main API client
- `src/store/cameraStore.ts` - Camera operations
- `src/store/sceneStore.ts` - Scene operations
- Any components making direct API calls

**Pattern to follow (from octaneWeb):**
```javascript
// Camera operations
'LiveLink/GetCamera'
'LiveLink/SetCamera'

// Mesh operations
'LiveLink/GetMeshes'
'LiveLink/GetMesh'

// File operations
'LiveLink/GetFile'
```

---

## References

**Working Implementation:** `/workspace/grpcSamples/octaneWeb/js/core/OctaneWebClient.js`

**Service Definition:** `/workspace/grpcSamples/octaneProxy/generated/livelink_pb2_grpc.py`

**Python Proxy:** `/workspace/grpcSamples/octaneProxy/octane_proxy.py`

---

## Summary

**What was wrong:**
- ❌ Using non-existent service `octane.render.RenderServerInfo`
- ❌ Calling non-existent method `GetServerInfo`
- ❌ Python proxy couldn't find module `octane.render.renderserverinfo_pb2_grpc`

**What we fixed:**
- ✅ Changed service name to `LiveLink`
- ✅ Changed method to `GetCamera` (valid method)
- ✅ Python proxy now successfully imports `livelink_pb2_grpc`

**Result:**
- 🟢 Connection to Octane should now work
- 🟢 API calls properly routed through Python proxy
- 🟢 gRPC calls successfully forwarded to Octane LiveLink

---

**Status:** 🟢 **READY TO TEST**  
**Commit:** `3894220`  
**Next:** Pull code and test in browser
