# octaneWebR Quick Start Guide

## 🚀 Single-Server Mode (NEW!)

The separate server has been eliminated. Everything runs in ONE Vite dev server.

---

## Step 1: Start the Server

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

---

## Step 2: Open the Application

### Browser
Open: **http://localhost:43929**

### Check Health Status
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

## Step 3: Connect to Octane (Optional)

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

Should show ONE Vite process (not two servers).

### Test 2: Health Endpoint
```bash
curl http://localhost:43929/api/health
```

Should return JSON with server status.

### Test 3: gRPC Proxy
```bash
curl -X POST http://localhost:43929/api/grpc/ApiProjectManager/rootNodeGraph \
  -H "Content-Type: application/json" \
  -d '{}'
```

**Without Octane**: Returns connection error (expected)
```json
{
  "error": "14 UNAVAILABLE: No connection established...",
  "service": "ApiProjectManager",
  "method": "rootNodeGraph",
  "code": 14
}
```

**With Octane**: Returns node graph data
```json
{
  "id": { "nodeHandle": 12345 },
  "name": "Root Node Graph",
  ...
}
```

---

## 🎛️ npm Scripts

### Production Scripts (Use These)
```bash
npm run dev      # ✅ Start single Vite server with gRPC proxy
npm run build    # ✅ Build production bundle
npm run preview  # ✅ Preview production build
```

### Legacy Scripts (Don't Use)
```bash
npm run dev:legacy     # ❌ Old two-server mode
npm run server:dev     # ❌ Separate Express server only
npm run client:dev     # ❌ Separate Vite server only
npm run build:legacy   # ❌ Old build process
```

---

## ✅ Success Checklist

After following this guide, you should have:

- [ ] Server running on http://localhost:43929
- [ ] Health endpoint returning JSON status
- [ ] gRPC proxy endpoint responding
- [ ] Single process (not two servers)
- [ ] Clean log output from one terminal

**If all checked**: ✅ **Setup Complete!**

---

**See ARCHITECTURE.md and BEFORE_AFTER.md for detailed documentation.**
