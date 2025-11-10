# octaneWeb2 Testing Instructions

**Status:** ✅ All APIs implemented and ready to test  
**Date:** 2025-11-10

---

## What's Been Completed

✅ **All 25+ API methods from octaneWeb implemented**  
✅ **9 complete gRPC services**  
✅ **Correct service/method naming (LiveLink, ApiRenderEngine, etc.)**  
✅ **Duplicate createNode method removed**  
✅ **Code committed and pushed to main branch**

---

## Testing Setup

### Prerequisites
1. **Octane Render** running with **LiveLink enabled** (Help → LiveLink)
2. **Python proxy server** running on your HOST machine (not in container)
3. **Vite dev server** for octaneWeb2

---

## Step 1: Start Python Proxy Server (On YOUR Machine)

The proxy needs to run on your HOST machine to connect to Octane:

```bash
# Navigate to the proxy directory
cd C:\otoyla\GRPC\dev\grpcSamples\octaneProxy

# Install dependencies (if not already installed)
pip install aiohttp grpcio protobuf

# Start the proxy server
python octane_proxy.py
```

**Expected output:**
```
Testing connection with GetCamera request
Successfully connected to Octane at localhost:51022
Initial camera state: pos=(x, y, z)
Proxy server running on http://0.0.0.0:51023
```

---

## Step 2: Start Vite Dev Server

In a new terminal on your HOST machine:

```bash
cd C:\otoyla\GRPC\dev\grpcSamples\octaneWeb2

# Install dependencies (if not already done)
npm install

# Start dev server
npm run dev
```

**Expected output:**
```
VITE v7.2.0  ready in XXX ms

➜  Local:   http://localhost:42219/
```

---

## Step 3: Open Browser and Test

### Open the Application
Navigate to: **http://localhost:42219**

### Open Browser Console
Press **F12** to open DevTools, then go to the **Console** tab

---

## Step 4: Test API Methods

### Test 1: Connection Test
```javascript
await octaneClient.connect()
```

**Expected:**
```
✅ Connected to Octane via LiveLink: {
  position: {...},
  target: {...},
  fov: 45,
  ...
}
```

---

### Test 2: Get Camera
```javascript
const camera = await octaneClient.getCamera()
console.log('Camera:', camera)
```

**Expected:**
```javascript
Camera: {
  position: { x: -0.29, y: 1.79, z: 21.59 },
  target: { x: 0, y: 0, z: 0 },
  fov: 45,
  ...
}
```

---

### Test 3: Set Camera Position
```javascript
// Move camera to new position
await octaneClient.setCamera(
  { x: 0, y: 5, z: 15 },  // new position
  { x: 0, y: 0, z: 0 }    // target
)
```

**Expected:**
- ✅ Camera should move in Octane viewport
- ✅ Console shows success (no errors)

---

### Test 4: Render Control
```javascript
// Stop rendering
await octaneClient.stopRendering()
// Expected: Render stops in Octane

// Restart rendering
await octaneClient.restartRendering()
// Expected: Render restarts in Octane

// Pause rendering
await octaneClient.pauseRendering()
// Expected: Render pauses

// Continue rendering
await octaneClient.continueRendering()
// Expected: Render continues

// Set render priority
await octaneClient.setRenderPriority(75)
// Expected: Priority changes
```

---

### Test 5: Project Management
```javascript
// Get current project info
const project = await octaneClient.getCurrentProject()
console.log('Project:', project)

// Reset project (New Project)
await octaneClient.resetProject()
// Expected: Octane creates new empty project

// Save project
await octaneClient.saveProject()
// Expected: Project saves
```

---

### Test 6: Scene Updates
```javascript
// Trigger scene update
await octaneClient.updateScene()
// Expected: Scene refreshes in Octane
```

---

### Test 7: Node Operations
```javascript
// Create a new diffuse material node
const node = await octaneClient.createNode('OctaneDiffuseMaterial')
console.log('Created node:', node)
// Expected: New material node created in Octane
```

---

### Test 8: Material Preview
```javascript
// Enable material preview
await octaneClient.enableMaterialRender()
// Expected: Material preview enabled

// Disable material preview
await octaneClient.disableMaterialRender()
// Expected: Material preview disabled
```

---

### Test 9: Cloud Services (If logged in)
```javascript
// Get subscription info
const sub = await octaneClient.getUserSubscriptionInfo()
console.log('Subscription:', sub)
// Expected: Your ORC subscription info
```

---

## Troubleshooting

### Error: "connect ECONNREFUSED 127.0.0.1:51023"
**Problem:** Python proxy is not running  
**Solution:** Start the proxy server (see Step 1)

### Error: "connect ECONNREFUSED 127.0.0.1:51022"
**Problem:** Octane is not running or LiveLink is disabled  
**Solution:**
1. Start Octane Render
2. Go to Help → LiveLink
3. Make sure LiveLink is enabled

### Error: "Failed to fetch" or CORS errors
**Problem:** Vite proxy configuration issue  
**Solution:**
1. Check vite.config.ts proxy settings
2. Restart Vite dev server

### Error: "Method not found" or "Service not found"
**Problem:** Service/method name mismatch  
**Solution:**
1. Check the service name matches exactly (case-sensitive)
2. Verify Python proxy has the protobuf module for that service

### Warning: "Duplicate member createNode"
**Problem:** Old duplicate method (now fixed)  
**Solution:** Already fixed in latest commit - pull the code

---

## Expected Behavior

### ✅ Success Indicators
- Proxy shows: `Successfully connected to Octane`
- Browser console shows: `✅ Connected to Octane via LiveLink`
- Camera moves in Octane when you call setCamera()
- Render stops/starts when you call render control methods
- No CORS errors
- No 404 errors

### ❌ Common Failures
- Proxy not running → Connection refused
- Octane not running → gRPC connection timeout
- LiveLink disabled → gRPC method not found
- Wrong service names → 404 or method not found

---

## Network Flow

```
Browser (localhost:42219)
    ↓ HTTP POST /api/LiveLink/GetCamera
Vite Proxy (removes /api prefix)
    ↓ HTTP POST /LiveLink/GetCamera
Python Proxy (localhost:51023)
    ↓ gRPC LiveLink.GetCamera()
Octane LiveLink (localhost:51022)
    ↓ Response
← ← ← Back to Browser
```

---

## Available API Services

All these services are now implemented and ready to test:

1. ✅ **LiveLink** - Camera operations
2. ✅ **ApiRenderEngine** - Render control
3. ✅ **ApiProjectManager** - Project management
4. ✅ **ApiChangeManager** - Scene updates
5. ✅ **ApiNode** - Node operations
6. ✅ **ApiNodeArray** - Array operations
7. ✅ **ApiItem** - Item properties
8. ✅ **ApiNodeGraphEditor** - Material preview
9. ✅ **ApiRenderCloudManager** - Cloud rendering

---

## Next Steps After Testing

Once basic API calls work:

1. **UI Integration** - Wire up buttons and controls
2. **Real-time Updates** - Implement camera sync on mouse drag
3. **Scene Browser** - Display scene tree with API data
4. **Node Graph** - Build visual node editor
5. **Render Controls** - Add toolbar buttons for render operations

---

## Documentation

- **OCTANEWEB_API_REFERENCE.md** - Complete API documentation
- **IMPLEMENTATION_COMPLETE.md** - Implementation summary
- **FIX_SERVICE_NAMES.md** - Service naming explanation
- **This Document** - Testing instructions

---

## Status Summary

🟢 **IMPLEMENTATION: COMPLETE**  
🟡 **TESTING: READY TO START**  
⏳ **UI INTEGRATION: PENDING**

**Last Updated:** 2025-11-10  
**Commit:** aa293f5 (Fix: Remove duplicate createNode method)
