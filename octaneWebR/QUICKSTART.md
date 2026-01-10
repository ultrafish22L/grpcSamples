# octaneWebR Quick Start Guide

## 🎯 Current Status

**OctaneWebR** is a React + TypeScript port of octaneWeb. Core features are production-ready.

**Working**: Scene Outliner, Node Inspector with real-time editing, Node Graph Editor, Live Render Viewport with camera controls  
**In Progress**: Material Database content, Render Toolbar actions (start/stop/pause), additional menu items

---

## 🚀 Quick Start

Everything runs in ONE Vite dev server with embedded gRPC proxy - no separate server needed.

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

## 🧪 Testing the Setup

### Test 1: Server Running
```bash
ps aux | grep vite | grep -v grep
```

Should show ONE Vite process with embedded gRPC proxy.

### Test 2: Health Endpoint
```bash
curl http://localhost:43929/api/health
```

Should return JSON with server status (`"status": "ok"` or `"unhealthy"`).

### Test 3: Browser Console
1. Open browser DevTools (F12)
2. Check Console tab for:
   - 📤 API request markers
   - ✅ API success responses
   - 🔄 Scene tree conversion logs (Node Graph)
   - 📌 Pin detection logs (Node Graph)
   - 🔗 Edge creation logs (Node Graph)

### Test 4: Menu Bar
- File menu should show: New, Open, Save, Save As, Recent Projects, Close, Exit
- Edit/Script/Module/Cloud/Window/Help menus should be present
- Click File → Recent Projects to see recent files (if any)

### Test 5: Scene Outliner
- Should show hierarchical tree with nodes like:
  - 📁 Scene
  - 🫖 teapot.obj (or your loaded model)
  - 🎯 Render target
  - 📷 Camera
  - 🌍 Environment

### Test 6: Node Inspector
- Click any node in Scene Outliner
- Right panel should show:
  - Node name and type
  - Expandable parameter groups
  - Input controls (checkboxes, number inputs, color pickers)

### Test 7: Node Graph Editor
- Bottom panel should show top-level nodes
- Right-click in graph for context menu (Materials, Geometry, Textures, etc.)
- Should see nodes with connections (cyan lines)

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

After following this guide, you should have:

- [ ] Server running on http://localhost:43929 (or port shown in terminal)
- [ ] Browser opens and shows octaneWebR interface
- [ ] Menu bar with File/Edit/Script/Module/Cloud/Window/Help menus
- [ ] Connection status shows "Connected" (if Octane running) or "Disconnected"
- [ ] Scene Outliner shows hierarchical tree (if Octane connected with scene loaded)
- [ ] Node Inspector shows properties when clicking nodes
- [ ] Node Graph Editor shows nodes with connections
- [ ] No TypeScript errors in terminal
- [ ] Single Vite process running (not two servers)

**If all checked**: ✅ **Setup Complete!**

---

## 🐛 Known Issues

### Material Database
**Status**: Live DB and Local DB tabs exist but content not implemented (planned)

### Render Toolbar Actions
**Status**: UI complete, most actions need API integration (start/stop/pause, clay mode, picking modes, etc.)

### Menu System
**Status**: Only 13/40+ menu items fully implemented (cloud.*, module.*, script.* menus missing)

---

## 📚 Additional Documentation

- **OVERVIEW.md** - Complete project overview and architecture
- **REPRO_PROMPT.md** - Quick onboarding guide for new development sessions
