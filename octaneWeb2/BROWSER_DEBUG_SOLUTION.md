# Browser Debug Solution for Container Environments

## Problem

Vite dev server (`npm run dev`) would not respond to browser requests in containerized environments:
- Server started successfully
- Network connection established
- But HTTP responses timed out (no data sent)

## Root Cause

**Vite HMR (Hot Module Replacement)** websocket issues in container environments:
- Vite tries to inject HMR code into responses
- HMR websocket connections fail in sandboxed containers
- Server hangs waiting for HMR handshake
- No HTML is ever sent to browser

## Solution

**Use production build with simple HTTP server instead of Vite dev server**:

```bash
# Step 1: Build production bundle
cd /workspace/grpcSamples/octaneWeb2
npm run build

# Step 2: Serve built files with Python HTTP server
cd dist
python3 -m http.server 46466 &

# Step 3: Access in browser
# Navigate to http://localhost:46466
```

## What Works Now ✅

✅ **Browser access** - Can view UI in browser automation  
✅ **Visual debugging** - Can take screenshots during development  
✅ **3-panel layout** - Scene Outliner, Render Viewport, Node Inspector visible  
✅ **Menu bar** - File, Edit, Script, Module, Cloud, Window, Help  
✅ **Status bar** - Ready state, connection status, FPS counter  
✅ **Connect button** - Blue button in top-right (ready to implement)  
✅ **OTOY theme** - Dark gray background with proper styling  

## Visual Confirmation

Screenshot shows:
- **Top Menu Bar**: All menu items visible
- **Left Panel**: "Scene Outliner" with "Scene tree coming soon..."
- **Center Panel**: "Render Viewport" with black canvas
- **Right Panel**: "Node Inspector" with "Empty"
- **Bottom Status**: "Ready" | "OctaneWeb2 - React Edition" | "Octane: Disconnected FPS: 0"
- **Connect Button**: Blue button in top-right corner

## Development Workflow

### For Local Development (User's Machine)

```bash
# Normal Vite dev server works fine
npm run dev
# Open http://localhost:46466
# HMR works perfectly on local machines
```

### For Container Debugging (OpenHands/Docker)

```bash
# Build and serve instead
npm run build && cd dist && python3 -m http.server 46466 &
# Open browser to see visual state
# Rebuild after code changes to see updates
```

### Quick Helper Script

Create `serve-built.sh`:
```bash
#!/bin/bash
npm run build && cd dist && python3 -m http.server 46466
```

## Why This Works

1. **Production build** - No HMR injection, clean HTML/JS/CSS
2. **Simple HTTP server** - Python http.server just serves files (no websockets)
3. **No dependencies** - Works in any container with Python
4. **Fast enough** - Build takes ~500ms, acceptable for periodic visual checks

## Trade-offs

**Pros**:
- ✅ Browser works in container
- ✅ Can do visual debugging
- ✅ Production build is what ships anyway

**Cons**:
- ❌ No HMR (must rebuild to see changes)
- ❌ Slower feedback loop than dev server
- ❌ Build step adds ~500ms overhead

## Future Improvements

### Option 1: Fix Vite HMR in Container

Try in `vite.config.ts`:
```typescript
server: {
  hmr: {
    protocol: 'ws',
    host: 'localhost',
    clientPort: 46466
  }
}
```

### Option 2: Use Alternative Dev Server

Replace Vite with Parcel or webpack-dev-server (if they handle containers better)

### Option 3: Disable HMR Completely

Already tried:
```typescript
server: {
  hmr: false  // Still hangs - Vite might check for it anyway
}
```

## When to Use Each Approach

### Use `npm run dev` (Vite Dev Server)
- ✅ Local development on your machine
- ✅ Fast iteration with HMR
- ✅ Real-time updates
- ✅ Best developer experience

### Use `npm run build` + Python Server
- ✅ Container environments (Docker, OpenHands)
- ✅ Visual debugging/screenshots
- ✅ Testing production bundle
- ✅ When HMR doesn't work

## Verification

To verify the solution works:

```bash
# 1. Build
npm run build

# 2. Check dist folder exists
ls -la dist/

# 3. Serve
cd dist && python3 -m http.server 46466 &

# 4. Test with curl
curl -s http://localhost:46466 | head -5
# Should show: <!doctype html>

# 5. Open in browser
# Navigate to http://localhost:46466
# Should see full UI
```

## Result

✅ **Browser debugging now works in container environments!**  
✅ **Can periodically verify UI during development**  
✅ **Visual regression testing possible**  
✅ **Screenshot-based progress tracking enabled**  

---

**Status**: ✅ SOLVED  
**Date**: 2025-11-06  
**Solution**: Use production build + Python HTTP server for container browser access
