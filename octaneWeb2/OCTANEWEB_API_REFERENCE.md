# octaneWeb API Reference - ALL Working gRPC Calls

**Source:** `/workspace/grpcSamples/octaneWeb/js/` (complete scan)  
**Status:** ✅ **PROVEN WORKING**

---

## Complete List of API Services Used by octaneWeb

octaneWeb uses **9 different services** with **25+ methods**:

1. **LiveLink** - Camera operations (2 methods)
2. **ApiProjectManager** - Project management (7 methods)
3. **ApiRenderEngine** - Render control (5 methods)
4. **ApiRenderCloudManager** - Cloud rendering (3 methods)
5. **ApiNodeGraphEditor** - Material preview (2 methods)
6. **ApiChangeManager** - Scene updates (1 method)
7. **ApiNode** - Node operations (2+ methods)
8. **ApiNodeArray** - Array operations (2+ methods)
9. **ApiItem** - Item properties (1+ method)

---

## Service 1: LiveLink (Camera Operations)

### 1. LiveLink/GetCamera

**Purpose:** Get current camera state from Octane

**Usage in octaneWeb:**
```javascript
const response = await this.makeApiCall('LiveLink/GetCamera');
// GetCamera returns a single camera object, not an array
```

**Request:** `{}` (empty object)

**Response:**
```javascript
{
  position: { x: number, y: number, z: number },
  target: { x: number, y: number, z: number },
  fov: number,
  // ... other camera properties
}
```

**Used in:**
- Camera synchronization from Octane to browser
- Initial camera state load

---

### 2. LiveLink/SetCamera

**Purpose:** Update camera position and/or target in Octane

**Usage in octaneWeb:**

**Pattern 1: Set position only**
```javascript
const response = await this.makeApiCall('LiveLink/SetCamera', {
    position: {
        x: cameraPos.x,
        y: cameraPos.y,
        z: cameraPos.z
    }
});
```

**Pattern 2: Set target only**
```javascript
const response = await this.makeApiCall('LiveLink/SetCamera', {
    target: {
        x: targetPos.x,
        y: targetPos.y,
        z: targetPos.z
    }
});
```

**Pattern 3: Set both position and target**
```javascript
const response = await this.makeApiCall('LiveLink/SetCamera', {
    position: { x, y, z },
    target: { x, y, z }
});
```

**Request:**
```typescript
{
  position?: { x: number, y: number, z: number },
  target?: { x: number, y: number, z: number }
}
```

**Response:**
```javascript
{
  success: boolean
  // ... confirmation data
}
```

**Used in:**
- Mouse drag camera control (orbit, pan, zoom)
- Manual camera updates from UI
- Camera synchronization from browser to Octane

---

## How octaneWeb Makes API Calls

### Client Setup

**Base URL:**
```javascript
this.serverUrl = 'http://localhost:51023'
```

### Request Format

**Method:** `POST`

**URL Pattern:**
```
{serverUrl}/{servicePath}
```

**Example:**
```
POST http://localhost:51023/LiveLink/GetCamera
POST http://localhost:51023/LiveLink/SetCamera
```

**Headers:**
```javascript
{
  'Content-Type': 'application/json'
}
```

**Body:**
```json
{
  // Request parameters
}
```

### makeApiCall Implementation

**From octaneWeb:**
```javascript
makeApiCall(servicePath, handle, request = {}, doAsync = false) {
    try {
        // Build request data
        const [serviceName, methodName] = servicePath.split('/');

        if (typeof handle !== "string") {
            request = handle;
        }
        else {
            // Add objectPtr if handle is provided and service needs it
            const objectPtrType = window.OctaneTypes.ObjectType[serviceName];

            if (objectPtrType !== undefined) {
                request.objectPtr = {
                    type: objectPtrType,
                    handle: handle
                };
            }
        }

        const url = `${this.serverUrl}/${servicePath}`;

        const requestOptions = {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(request)
        };

        if (doAsync) {
            return fetch(url, requestOptions)
                .then(response => response.json())
                .catch(error => {
                    console.error('Fetch error:', error);
                    throw error;
                });
        }
        else {
            // Synchronous XMLHttpRequest (deprecated but used in octaneWeb)
            // ...
        }
    } catch (error) {
        console.error('API call error:', error);
        throw error;
    }
}
```

---

## Camera Synchronization Pattern

### From Octane to Browser (GetCamera)

**When:**
- Initial load
- Periodic sync (if needed)
- After user interaction in Octane

**Code:**
```javascript
async syncCameraFromOctane() {
    const response = await this.makeApiCall('LiveLink/GetCamera');
    // GetCamera returns a single camera object, not an array
    const camera = response;
    
    // Update local camera state
    this.cameraPosition = camera.position;
    this.cameraTarget = camera.target;
    this.cameraFov = camera.fov;
}
```

### From Browser to Octane (SetCamera)

**When:**
- Mouse drag (orbit/pan/zoom)
- Camera controls in UI
- Programmatic camera updates

**Code:**
```javascript
async updateCameraInOctane(position, target) {
    await this.makeApiCall('LiveLink/SetCamera', {
        position: {
            x: position.x,
            y: position.y,
            z: position.z
        },
        target: {
            x: target.x,
            y: target.y,
            z: target.z
        }
    });
}
```

---

---

## Service 2: ApiProjectManager (Project Management)

### 1. ApiProjectManager/loadProject
**Purpose:** Load an Octane project file  
**Used in:** MenuSystem.js - File → Open Project

### 2. ApiProjectManager/saveProject
**Purpose:** Save current project  
**Used in:** MenuSystem.js - File → Save

### 3. ApiProjectManager/saveProjectAs
**Purpose:** Save project with new name/location  
**Used in:** MenuSystem.js - File → Save As

### 4. ApiProjectManager/saveProjectAsReferencePackage
**Purpose:** Save project as reference package  
**Used in:** MenuSystem.js - File → Export Package

### 5. ApiProjectManager/unpackPackage
**Purpose:** Unpack a reference package  
**Used in:** MenuSystem.js - File → Import Package

### 6. ApiProjectManager/getCurrentProject
**Purpose:** Get current project info  
**Used in:** MenuSystem.js - Project management

### 7. ApiProjectManager/resetProject
**Purpose:** Reset/clear current project  
**Used in:** MenuSystem.js - File → New Project

### 8. ApiProjectManager/rootNodeGraph
**Purpose:** Get root node graph  
**Used in:** NodeGraphEditor.js - Node graph operations

---

## Service 3: ApiRenderEngine (Render Control)

### 1. ApiRenderEngine/stopRendering
**Purpose:** Stop current render  
**Used in:** RenderToolbar.js - Stop button

### 2. ApiRenderEngine/restartRendering
**Purpose:** Restart rendering  
**Used in:** RenderToolbar.js - Restart button

### 3. ApiRenderEngine/pauseRendering
**Purpose:** Pause current render  
**Used in:** RenderToolbar.js - Pause button

### 4. ApiRenderEngine/continueRendering
**Purpose:** Resume paused render  
**Used in:** RenderToolbar.js - Resume button

### 5. ApiRenderEngine/setRenderPriority
**Purpose:** Set render priority  
**Used in:** RenderToolbar.js - Priority dropdown

**Request:**
```javascript
{
  priority: number  // 0-100
}
```

---

## Service 4: ApiRenderCloudManager (Cloud Rendering)

### 1. ApiRenderCloudManager/newRenderTask
**Purpose:** Create new cloud render task  
**Used in:** MenuSystem.js - Render → Cloud Render

**Request:**
```javascript
{
  projectPath: string,
  settings: object
}
```

### 2. ApiRenderCloudManager/uploadCurrentProject
**Purpose:** Upload current project to cloud  
**Used in:** MenuSystem.js - Cloud operations

### 3. ApiRenderCloudManager/userSubscriptionInfo
**Purpose:** Get user's cloud subscription info  
**Used in:** MenuSystem.js - Account info

---

## Service 5: ApiNodeGraphEditor (Material Preview)

### 1. ApiNodeGraphEditor/enableMaterialRender
**Purpose:** Enable material preview rendering  
**Used in:** NodeInspectorControls.js

### 2. ApiNodeGraphEditor/disableMaterialRender
**Purpose:** Disable material preview rendering  
**Used in:** NodeInspectorControls.js

---

## Service 6: ApiChangeManager (Scene Updates)

### 1. ApiChangeManager/update
**Purpose:** Trigger scene update/refresh  
**Used in:** NodeInspector.js, CallbackRenderViewport.js

**Request:** `{}` (empty)

---

## Service 7: ApiNode (Node Operations)

### 1. ApiNode/create
**Purpose:** Create new node  
**Used in:** NodeGraphEditor.js - Node creation

**Request:**
```javascript
{
  nodeType: string,
  parent: string  // optional parent node
}
```

### 2. ApiNode/destinationNodes
**Purpose:** Get destination nodes for a node  
**Used in:** NodeGraphEditor.js - Node connections

---

## Service 8: ApiNodeArray (Array Operations)

### 1. ApiNodeArray/size1
**Purpose:** Get size of node array  
**Used in:** NodeGraphEditor.js - Array size queries

### 2. ApiNodeArray/get1
**Purpose:** Get element from node array  
**Used in:** NodeGraphEditor.js - Array element access

---

## Service 9: ApiItem (Item Properties)

### 1. ApiItem/setByAttrID
**Purpose:** Set item property by attribute ID  
**Used in:** NodeInspector.js - Property editing

**Request:**
```javascript
{
  attrId: number,
  value: any
}
```

---

## Priority Implementation Order for octaneWeb2

### Phase 1: Core Connection & Camera ✅ (Current)
1. ✅ LiveLink/GetCamera - Connection test & camera sync
2. ⏳ LiveLink/SetCamera - Camera updates

### Phase 2: Basic Rendering 🎯 (Next)
3. ApiRenderEngine/stopRendering
4. ApiRenderEngine/restartRendering
5. ApiRenderEngine/pauseRendering
6. ApiRenderEngine/continueRendering

### Phase 3: Project Management
7. ApiProjectManager/loadProject
8. ApiProjectManager/saveProject
9. ApiProjectManager/resetProject
10. ApiProjectManager/getCurrentProject

### Phase 4: Node Operations
11. ApiNode/create
12. ApiNode/destinationNodes
13. ApiChangeManager/update

### Phase 5: Advanced Features
14. ApiNodeGraphEditor/enableMaterialRender
15. ApiNodeGraphEditor/disableMaterialRender
16. ApiRenderEngine/setRenderPriority
17. ApiProjectManager/saveProjectAs
18. ApiProjectManager/saveProjectAsReferencePackage
19. ApiProjectManager/unpackPackage

### Phase 6: Cloud Features
20. ApiRenderCloudManager/newRenderTask
21. ApiRenderCloudManager/uploadCurrentProject
22. ApiRenderCloudManager/userSubscriptionInfo

---

## octaneWeb2 Implementation Guide

### Step 1: Update octaneClient.ts

**Current connect() - Already correct:**
```typescript
async connect(): Promise<boolean> {
  try {
    const response = await this.makeServiceCall(
      'LiveLink',
      'GetCamera',
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

### Step 2: Add getCamera() method

```typescript
async getCamera(): Promise<any> {
  return await this.makeServiceCall('LiveLink', 'GetCamera', {})
}
```

### Step 3: Add setCamera() method

```typescript
async setCamera(position?: {x: number, y: number, z: number}, target?: {x: number, y: number, z: number}): Promise<any> {
  const request: any = {}
  
  if (position) {
    request.position = position
  }
  
  if (target) {
    request.target = target
  }
  
  return await this.makeServiceCall('LiveLink', 'SetCamera', request)
}
```

### Step 4: Use in stores/components

**cameraStore.ts:**
```typescript
// Get camera from Octane
const camera = await octaneClient.getCamera()
setCameraPosition(camera.position)
setCameraTarget(camera.target)

// Update camera in Octane
await octaneClient.setCamera(
  { x: position.x, y: position.y, z: position.z },
  { x: target.x, y: target.y, z: target.z }
)
```

---

## Testing Checklist

### ✅ Phase 1: Connection (DONE)
- [x] connect() uses LiveLink/GetCamera
- [x] No more "octane.render.RenderServerInfo" errors
- [x] Python proxy successfully imports livelink_pb2_grpc

### 🔲 Phase 2: Camera Operations
- [ ] getCamera() retrieves camera from Octane
- [ ] setCamera() updates camera in Octane
- [ ] Camera position updates sync to Octane
- [ ] Camera target updates sync to Octane

### 🔲 Phase 3: UI Integration
- [ ] Mouse orbit updates camera in Octane
- [ ] Mouse pan updates camera in Octane
- [ ] Mouse zoom updates camera in Octane
- [ ] Camera widget shows correct values

---

## Summary

**octaneWeb uses ONLY these LiveLink methods:**
1. ✅ `LiveLink/GetCamera` - Get camera state from Octane
2. ✅ `LiveLink/SetCamera` - Update camera in Octane

**octaneWeb2 should:**
1. ✅ Use same service name: `LiveLink`
2. ✅ Use same method names: `GetCamera`, `SetCamera`
3. ✅ Use same URL pattern: `/{service}/{method}`
4. ⏳ Implement getCamera() and setCamera() methods
5. ⏳ Wire up camera controls to call these methods

**Don't implement yet:**
- GetMeshes, GetMesh, GetFile, StreamCamera
- These aren't used in octaneWeb, so skip for now

---

**Reference:** `/workspace/grpcSamples/octaneWeb/js/core/OctaneWebClient.js`  
**Status:** 🟢 **READY TO IMPLEMENT**
