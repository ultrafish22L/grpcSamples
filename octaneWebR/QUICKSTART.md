# octaneWebR Quick Start Guide

## 🚀 Quick Start

**One command starts everything** - Vite dev server with embedded gRPC proxy.

### Prerequisites & First-Time Setup

**Install Dependencies** (first time only):

```bash
cd /workspace/project/grpcSamples/octaneWebR
npm install
```

**Key Dependencies**:
- **ReactFlow v12** (`@xyflow/react ^12.10.0`) - Node graph editor library
- **React 18** - UI framework
- **TypeScript** - Type safety
- **Vite** - Build tool and dev server
- **@grpc/grpc-js** - gRPC client for Node.js

**If you need to install/update ReactFlow v12 specifically**:

```bash
npm install @xyflow/react@^12.10.0
```

> **Note**: ReactFlow v12 uses the new package name `@xyflow/react` (not the old `reactflow` package). The Node Graph Editor follows ReactFlow v12 best practices with proper edge interactions, context menus, and semantic HTML.

**Dependencies are auto-installed** when you run `npm run dev` for the first time, so you can skip this step if you're in a hurry.

---

### Step 1: Start the Server

```bash
cd /workspace/project/grpcSamples/octaneWebR
npm run dev
```

**Expected Output**:
```
📡 Vite gRPC Plugin: Connected to Octane at 127.0.0.1:51022
📦 Proto files ready for lazy loading
✅ Proto definitions will be loaded on-demand per service
✅ Octane gRPC Plugin configured
   • HTTP API: /api/grpc/:service/:method
   • WebSocket: /api/callbacks
   • Health: /api/health

VITE v5.4.21  ready in 148 ms

➜  Local:   http://localhost:43929/
➜  Network: http://172.17.0.3:43929/
```

### Step 2: Open the Application

**Browser**: Open **http://localhost:43929** (or the port shown in terminal output)

The application will load with:
- **Menu Bar** (top) - File/Edit/Script/Module/Cloud/Window/Help menus
- **Scene Outliner** (left panel) - Shows "Loading scene..." until Octane connects
- **Node Inspector** (right panel) - Shows properties of selected node
- **Callback Render Viewport** (center panel) - Real-time rendering with mouse camera controls
- **Node Graph Editor** (bottom panel) - Visual node graph with context menus
- **Connection Status** (top right) - Shows "Connected" or "Disconnected"

---

### Step 3: Check System Health (Optional)

```bash
curl http://localhost:43929/api/health | python -m json.tool
```

**Response (Octane not running)**:
```json
{
  "status": "unhealthy",
  "octane": "disconnected",
  "server": "vite",
  "timestamp": "2025-01-20T01:47:40.573Z"
}
```

**Response (Octane running)**:
```json
{
  "status": "ok",
  "octane": "connected",
  "server": "vite",
  "timestamp": "2025-01-20T01:47:40.573Z"
}
```

---

## 🎨 Connecting to Octane

### If Octane is Installed Locally

1. **Start Octane Render**
2. **Enable LiveLink**:
   - Menu: `Help → LiveLink`
   - Verify port 51022 is open
3. **Reload octaneWebR** in browser

### If Octane is Not Installed

The application will still start and serve the UI, but API calls will fail gracefully with connection errors. This is expected and allows development without Octane.

---

## 🐛 Debugging & Development

### Debugging Best Practices

**MINIMIZE visual debug sessions** - check these FIRST:

1. **TypeScript Errors**:
   ```bash
   npm run build       # Full build with type checking
   tsc --noEmit        # Type check only (faster)
   ```

2. **Runtime Errors** - Browser Console (F12):
   - 📤 API requests
   - ✅ API successes
   - ❌ API errors
   - 🔄 Scene conversions
   - 📌 Pin detections
   - 🔗 Edge creations

3. **Connection Issues**:
   ```bash
   curl http://localhost:43929/api/health | python -m json.tool
   ```
   Should show `"status": "ok"` if Octane connected.

**Only use visual debugger when**:
- Logs don't reveal the issue
- Complex state mutations
- Async race conditions

### Quick Checks

```bash
# Check server running
ps aux | grep vite | grep -v grep

# Check TypeScript
tsc --noEmit

# Check health
curl http://localhost:43929/api/health
```

### Testing After Changes

1. Open browser console (F12) - Check for errors
2. Test UI interaction - Scene Outliner, Node Inspector, Node Graph
3. Run build - `npm run build` to catch type errors
4. Test with Octane connected - Verify real API calls work

---

## 🎛️ Available Commands

```bash
npm run dev              # Start development server (single-server mode)
npm run build            # Build production bundle
npm run preview          # Preview production build
npm run proto:generate   # Regenerate TypeScript types from .proto files
tsc --noEmit             # TypeScript type checking only (no build)
```

---

## ✅ Success Checklist

Quick verification:

```bash
# 1. Server running
ps aux | grep vite | grep -v grep  # Should show one process

# 2. Health check
curl http://localhost:43929/api/health  # Should return JSON

# 3. TypeScript clean
tsc --noEmit  # Should show no errors
```

**Browser**:
- Open http://localhost:43929
- Check console (F12) - No errors
- Connection status shows "Connected" (green) if Octane running
- Scene Outliner shows tree if Octane has scene loaded

**If all pass**: ✅ **Setup Complete!**

---

## 📚 More Documentation

- **OVERVIEW.md** - Architecture, debugging practices, development workflow
- **IMPLEMENTATION_PLAN.md** - Feature roadmap
- **CODE_REVIEW.md** - Code quality guidelines

---

**Last Updated**: 2025-01-23  
**Recent Fixes**:
- ReactFlow v12 best practices: Context menus refactored, edge interactions added, dead code removed (commit 3ed0ccbd)
- ReactFlow edge clicks enabled with CSS pointer-events (commit 471bacc9)
- Output pin colors use nodeInfo.nodeColor (commit a1f2be66)

---

## API Development Best Practices

### Always Verify API Method Names

**Before implementing any API call, check the proto files!** Never assume method names.

**Example**:
```typescript
// WRONG (assumed name - will fail at runtime)
await client.callApi('ApiItem', 'deleteItem', nodeHandle, {});

// CORRECT (verified in apinodesystem_3_pb2_grpc.py)
await client.callApi('ApiItem', 'destroy', nodeHandle, {});
```

**How to Verify**:
```bash
# Find proto file for ApiItem
cd /grpcSamples/octaneProxy/generated
grep -A 100 "class ApiItemServiceStub" apinodesystem_3_pb2_grpc.py

# Look for method definitions like:
# self.destroy = channel.unary_unary(...)
```

**Proto files location**: `/grpcSamples/octaneProxy/generated/*_pb2_grpc.py`

See `OCTANE_API_REFERENCE.md` for complete API documentation and workflow.
