# Networking Setup and Browser Debugging

## Overview

OctaneWeb2 uses a multi-tier architecture to communicate with Octane LiveLink. Understanding this setup is essential for debugging and development.

## Network Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│ Browser (user's machine)                                        │
│ http://localhost:42219                                          │
│ React App served by Vite dev server                             │
└────────────────┬────────────────────────────────────────────────┘
                 │ HTTP requests to /api/*
                 ↓
┌─────────────────────────────────────────────────────────────────┐
│ Vite Dev Server (port 42219)                                    │
│ - Serves React app                                              │
│ - Proxies /api/* requests to Python server                      │
│ - Rewrites /api/rpc/... → /rpc/...                             │
└────────────────┬────────────────────────────────────────────────┘
                 │ HTTP proxied to 127.0.0.1:51023
                 ↓
┌─────────────────────────────────────────────────────────────────┐
│ Python Proxy Server (port 51023)                                │
│ ../octaneProxy/octane_proxy.py                                  │
│ - Converts HTTP/JSON to gRPC                                    │
│ - Handles CORS                                                  │
│ - Manages callback streaming                                    │
└────────────────┬────────────────────────────────────────────────┘
                 │ gRPC to 127.0.0.1:51022 (or host.docker.internal in Docker)
                 ↓
┌─────────────────────────────────────────────────────────────────┐
│ Octane LiveLink Service (port 51022)                            │
│ OctaneRender Standalone                                         │
│ Enable via: Help → LiveLink                                     │
└─────────────────────────────────────────────────────────────────┘
```

## Port Configuration

| Service | Port | Protocol | Purpose |
|---------|------|----------|---------|
| Vite Dev Server | 42219 | HTTP | Serves React app |
| Python Proxy | 51023 | HTTP/JSON | HTTP-to-gRPC bridge |
| Octane LiveLink | 51022 | gRPC | Octane API |

## IPv4 vs IPv6 Issue

**Important**: Node.js and Python prefer IPv6 by default, but Octane LiveLink only listens on IPv4.

### Problem

- `localhost` resolves to `::1` (IPv6) first on many systems
- Octane LiveLink only listens on `127.0.0.1` (IPv4)
- Connections to `::1:51022` fail with "Connection refused"

### Solution

Both the Python proxy and Vite config force IPv4:

**Python proxy** (`octane_proxy.py`):
```python
# Force IPv4 address family (prevents IPv6 ::1 connection attempts)
import socket
# ... in connect_to_octane():
channel = grpc.aio.insecure_channel(
    'host.docker.internal:51022',
    options=[('grpc.default_authority', 'host.docker.internal')]
)
```

**Vite config** (`vite.config.ts`):
```typescript
import http from 'http'

// Force DNS to prefer IPv4
process.env.NODE_OPTIONS = '--dns-result-order=ipv4first'

export default defineConfig({
  server: {
    proxy: {
      '/api': {
        target: 'http://127.0.0.1:51023',  // Use 127.0.0.1, not localhost!
        agent: new http.Agent({
          family: 4  // Force IPv4
        })
      }
    }
  }
})
```

## Docker/Sandbox Environments

When running in Docker or sandboxed environments (like OpenHands), the host machine's localhost is not accessible.

### Solution: host.docker.internal

Replace `127.0.0.1` with `host.docker.internal` in the Python proxy:

```python
# In octane_proxy.py
OCTANE_ADDRESS = 'host.docker.internal:51022'  # Instead of '127.0.0.1:51022'
```

This special hostname resolves to the host machine's IP address from inside Docker.

## Browser Debugging Setup

### For Agent Self-Testing (OpenHands)

The agent can test the application in its own browser:

1. **Start Python proxy** (from octaneProxy folder):
   ```bash
   cd /workspace/grpcSamples/octaneProxy
   python octane_proxy.py &
   ```

2. **Build React app**:
   ```bash
   cd /workspace/grpcSamples/octaneWeb2
   npm run build
   ```

3. **Serve dist folder** on available port:
   ```bash
   cd /workspace/grpcSamples/octaneWeb2/dist
   python3 -m http.server 48537 --bind 0.0.0.0 &
   ```

4. **Access in browser**:
   - Agent: `goto("http://localhost:48537")`
   - User: `http://localhost:48537` (port mapped from Docker)

### For User Local Testing

Users run both dev server and proxy locally:

1. **Start Python proxy**:
   ```bash
   cd octaneProxy
   python octane_proxy.py
   ```

2. **Start Vite dev server**:
   ```bash
   cd octaneWeb2
   npm run dev
   ```

3. **Open browser**: `http://localhost:42219`

## Debugging Connection Issues

### Check Octane LiveLink

1. Open OctaneRender Standalone
2. Menu: Help → LiveLink
3. Verify "Enable LiveLink" is checked
4. Verify port is 51022

### Test Python Proxy

```bash
# Check if proxy is running
curl http://127.0.0.1:51023/health

# Test basic API call
curl -X POST http://127.0.0.1:51023/rpc/octane.base.Base/GetOctaneVersion \
  -H "Content-Type: application/json" \
  -d '{}'
```

### Check Vite Proxy

Open browser console (F12) and look for:
- Network requests to `/api/rpc/...`
- Response headers showing CORS headers
- Console errors about connection failures

### Common Errors

| Error | Cause | Solution |
|-------|-------|----------|
| `ECONNREFUSED ::1:51023` | IPv6 attempted first | Use `127.0.0.1` not `localhost` |
| `ECONNREFUSED 127.0.0.1:51022` | Octane not running | Start Octane, enable LiveLink |
| `404 Not Found /api/...` | Vite proxy not configured | Check vite.config.ts proxy settings |
| `CORS policy` | Direct connection to proxy | Use Vite dev server, not direct proxy URL |
| `Connection refused 10061` | Octane LiveLink disabled | Enable in Help → LiveLink menu |

## CORS Headers

The Python proxy adds these headers for browser compatibility:

```python
response.headers['Access-Control-Allow-Origin'] = '*'
response.headers['Access-Control-Allow-Methods'] = 'GET, POST, OPTIONS'
response.headers['Access-Control-Allow-Headers'] = 'Content-Type, X-Call-Id'
response.headers['Access-Control-Expose-Headers'] = 'X-Call-Id'
```

The Vite proxy forwards these headers to the browser.

## Development Workflow

1. **Terminal 1**: Run Python proxy
   ```bash
   cd octaneProxy
   python octane_proxy.py
   ```

2. **Terminal 2**: Run Vite dev server
   ```bash
   cd octaneWeb2
   npm run dev
   ```

3. **Terminal 3**: Run Octane Standalone
   - Enable LiveLink (Help → LiveLink)
   - Load a scene

4. **Browser**: Open `http://localhost:42219`
   - Open DevTools (F12)
   - Click "Connect" button
   - Verify "Connected" status in UI

5. **Check Console**: Should see:
   ```
   🚀 OctaneWeb2 starting...
   🔌 Connecting to Octane...
   ✅ Connected to Octane
   🔄 Loading scene from Octane...
   ✅ Scene loaded: N root nodes
   ```

## Production Deployment

For production, build the React app and serve the static files:

```bash
npm run build
cd dist
python3 -m http.server 8080
```

Then configure the proxy target appropriately for your environment.
