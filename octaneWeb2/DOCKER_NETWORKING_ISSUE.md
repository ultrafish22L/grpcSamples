# Docker Networking Issue - octaneWeb2

**Date:** 2025-11-10  
**Environment:** Docker Sandbox (OpenHands)  
**Status:** 🔴 BLOCKED - Python proxy not accessible from Docker container

## Current Situation

### What's Working:
✅ Vite dev server running on port 40800 in Docker container  
✅ Node.js installed and dependencies ready  
✅ Code changes committed and pushed  

### What's NOT Working:
❌ Docker container cannot reach Python proxy on host machine  
❌ Python proxy likely bound to `127.0.0.1:51023` (localhost only)  
❌ Needs to be bound to `0.0.0.0:51023` (all interfaces)  

## Error Details

### From Vite logs:
```
9:28:26 PM [vite] http proxy error: /rpc/octane.render.RenderServerInfo/GetServerInfo
Error: connect ECONNREFUSED 192.168.65.254:51023
```

**Translation:**
- `host.docker.internal` resolves to `192.168.65.254` (Docker host)
- Connection to port `51023` on that IP is refused
- This means the Python proxy is either:
  1. Not running, OR
  2. Running but bound to `127.0.0.1` (not accessible from Docker)

## Required Fix (On Your Host Machine)

### Check Python Proxy Binding

Your Python proxy is probably starting with:
```python
web.run_app(app, host='127.0.0.1', port=51023)  # ❌ Only localhost
```

It needs to be:
```python
web.run_app(app, host='0.0.0.0', port=51023)  # ✅ All interfaces
```

### Verification Steps

1. **Check current proxy binding:**
   ```bash
   # On your host machine (not in Docker)
   netstat -an | grep 51023
   # or
   lsof -i :51023
   ```

   **Good output (accessible from Docker):**
   ```
   tcp        0      0 0.0.0.0:51023           0.0.0.0:*               LISTEN
   ```

   **Bad output (localhost only):**
   ```
   tcp        0      0 127.0.0.1:51023         0.0.0.0:*               LISTEN
   ```

2. **Check Python proxy code:**
   ```bash
   # On your host machine
   grep -n "run_app" octaneProxy/octane_proxy.py
   ```

   Look for the line that starts the server. According to the octaneWeb/NETWORKING.md docs, it **should already** bind to `0.0.0.0`.

3. **Restart Python proxy with correct binding:**
   ```bash
   # On your host machine
   cd octaneProxy
   python octane_proxy.py
   ```

   **Expected startup output:**
   ```
   Octane gRPC Passthrough Proxy Server
   Proxy Port: 51023
   Octane Target: 127.0.0.1:51022
   Docker Support: false
   Testing connection with GetCamera request
   Successfully connected to Octane at 127.0.0.1:51022
   Initial camera state: pos=(-0.29, 1.79, 21.59)
   Proxy server running on http://0.0.0.0:51023  ← Must say 0.0.0.0
   ```

## Architecture Overview

### Current Setup (Sandbox Environment):

```
┌─────────────────────────────────────────────────────────────┐
│ HOST MACHINE (Your Computer)                                │
│                                                              │
│  ┌──────────┐         ┌──────────────┐      ┌──────────┐  │
│  │  Octane  │ ◄─────► │ Python Proxy │      │ Browser  │  │
│  │  :51022  │  gRPC   │   :51023     │      │          │  │
│  └──────────┘         └──────┬───────┘      └────┬─────┘  │
│                               │                   │         │
│                               │ (need 0.0.0.0)    │         │
└───────────────────────────────┼───────────────────┼─────────┘
                                │                   │
                                │                   │ HTTP
                         Docker Network             │
                                │                   │
┌───────────────────────────────┼───────────────────┼─────────┐
│ DOCKER CONTAINER (OpenHands Sandbox)              │         │
│                               │                   │         │
│                               ▼                   ▼         │
│                    host.docker.internal:51023  :40800      │
│                               │                   │         │
│                          ┌────┴──────┐       ┌───┴────┐   │
│                          │   Vite    │◄──────│ React  │   │
│                          │   Proxy   │       │  App   │   │
│                          └───────────┘       └────────┘   │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Key Points:

1. **Docker → Host Communication:**
   - Docker uses `host.docker.internal` to reach host machine
   - This resolves to host's IP (192.168.65.254 in your case)
   - Services on host must bind to `0.0.0.0` to be accessible

2. **Browser → Docker Communication:**
   - Browser accesses Docker container on port 40800
   - This port is mapped to host machine

3. **The Gap:**
   - Python proxy must bind to `0.0.0.0:51023`
   - Otherwise Docker can't reach it
   - Connection refused at host.docker.internal:51023

## Solutions

### Solution 1: Fix Python Proxy Binding (RECOMMENDED)

**On your host machine:**

1. Check if `octane_proxy.py` already uses `0.0.0.0`:
   ```bash
   grep "run_app" octaneProxy/octane_proxy.py
   ```

2. If it says `127.0.0.1`, change it to `0.0.0.0`:
   ```python
   # At the end of octane_proxy.py
   web.run_app(app, host='0.0.0.0', port=PROXY_PORT)
   ```

3. Restart the proxy:
   ```bash
   # Stop current proxy
   # Then start fresh
   python octane_proxy.py
   ```

4. **Verify from Docker:**
   ```bash
   # In Docker container (this terminal)
   curl -s http://host.docker.internal:51023/health
   ```

   **Expected:** `{"status": "ok", "connected": true}`

---

### Solution 2: Run Everything Locally (Alternative)

If Docker networking is too complex, you can run octaneWeb2 directly on your host machine:

**On your host machine:**
```bash
cd octaneWeb2
npm install
npm run dev
```

**Access:** `http://localhost:42219` (or whatever port Vite chooses)

**Benefits:**
- No Docker networking issues
- Simpler setup
- Faster development cycle

**Vite config for local development:**
```typescript
proxy: {
  '/api': {
    target: 'http://127.0.0.1:51023',  // Local proxy
    changeOrigin: true,
    rewrite: (path) => path.replace(/^\/api/, '')
  }
}
```

---

### Solution 3: Create Environment-Specific Config

Update `vite.config.ts` to detect environment:

```typescript
import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import path from 'path'

const isDocker = process.env.DOCKER === 'true' || 
                 process.cwd().includes('/workspace')

export default defineConfig({
  plugins: [react()],
  server: {
    port: isDocker ? 40800 : 42219,
    host: '0.0.0.0',
    cors: true,
    strictPort: false,
    proxy: {
      '/api': {
        target: isDocker 
          ? 'http://host.docker.internal:51023'  // Docker sandbox
          : 'http://127.0.0.1:51023',            // Local dev
        changeOrigin: true,
        rewrite: (path) => path.replace(/^\/api/, '')
      }
    }
  },
  resolve: {
    alias: {
      '@': path.resolve(__dirname, './src'),
    }
  }
})
```

## Current File Status

### Changed Files (Already Committed):
- ✅ `src/api/octaneClient.ts` - Changed to use `/api` relative URLs
- ✅ `vite.config.ts` - Configured proxy to Python proxy
- ✅ Documentation files created

### Configuration Status:
- **Port:** 40800 (Docker sandbox)
- **Proxy Target:** `http://host.docker.internal:51023`
- **Proxy Rewrite:** Removes `/api` prefix
- **CORS:** Enabled

## Next Steps

### For You (On Host Machine):

1. **Check Python proxy binding:**
   ```bash
   netstat -an | grep 51023
   ```

2. **If bound to 127.0.0.1, restart with 0.0.0.0:**
   - Stop current proxy
   - Ensure `octane_proxy.py` uses `host='0.0.0.0'`
   - Start proxy again

3. **Verify accessibility:**
   ```bash
   # From host machine
   curl http://localhost:51023/health
   
   # Should return: {"status": "ok", "connected": true}
   ```

4. **Test from browser:**
   - Open: `http://localhost:40800`
   - Check console for connection status
   - Should NOT see CORS or connection refused errors

### For Me (In Docker):

Once you confirm the proxy is accessible, I can:
1. Test the application in my browser
2. Verify the CORS fix works end-to-end
3. Check for any remaining issues
4. Update documentation with final working configuration

## Testing Commands

### From Docker (I can run these):
```bash
# Test proxy health
curl -s http://host.docker.internal:51023/health

# Test specific API call
curl -X POST http://host.docker.internal:51023/rpc/octane.render.RenderServerInfo/GetServerInfo \
  -H "Content-Type: application/json" \
  -d '{}'
```

### From Host (You can run these):
```bash
# Check proxy binding
lsof -i :51023

# Check proxy logs
tail -20 /tmp/octane_proxy.log  # If running in background

# Test proxy locally
curl http://localhost:51023/health
```

## Summary

**The Issue:** Python proxy not accessible from Docker because it's bound to `127.0.0.1` instead of `0.0.0.0`.

**The Fix:** Ensure Python proxy binds to `0.0.0.0:51023` on your host machine.

**Then:** Everything should work:
- Browser → Vite (40800) → Vite Proxy → host.docker.internal:51023 → Python Proxy → Octane

**Status:** Waiting for Python proxy to be accessible with `0.0.0.0` binding.
