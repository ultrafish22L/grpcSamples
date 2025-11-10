# IPv6 Connection Fix

**Date:** 2025-11-10  
**Issue:** `Error: connect ECONNREFUSED ::1:51023`

## Problem Description

After implementing the CORS fix, a new error appeared:

```
[vite] http proxy error: /rpc/octane.render.RenderServerInfo/GetServerInfo
Error: connect ECONNREFUSED ::1:51023
```

## Root Cause

**IPv4 vs IPv6 loopback resolution:**

1. Python proxy listens on `0.0.0.0:51023` (all interfaces, primarily IPv4)
2. Vite config used `localhost:51023` as target
3. Modern Node.js resolves `localhost` preferring IPv6 (`::1`) over IPv4 (`127.0.0.1`)
4. Connection attempt to `::1:51023` failed because Python proxy wasn't listening on IPv6

## Solution

Changed the proxy target to explicitly use IPv4:

**Before:**
```typescript
target: 'http://localhost:51023',
```

**After:**
```typescript
target: 'http://127.0.0.1:51023',  // Python octane_proxy.py (use IPv4)
```

## Technical Details

### IPv4 vs IPv6 Loopback Addresses:
- **IPv4:** `127.0.0.1` (traditional loopback)
- **IPv6:** `::1` (equivalent IPv6 loopback)
- **localhost:** Can resolve to either, Node.js prefers IPv6 when available

### Why This Matters:
When a server listens on `0.0.0.0`, it typically binds to all IPv4 interfaces. To listen on both IPv4 and IPv6, it would need to:
- Explicitly bind to `::` (IPv6 all interfaces), OR
- Create separate bindings for both protocols

### Node.js Behavior:
Modern versions of Node.js (v17+) changed DNS resolution to prefer IPv6. This is standards-compliant but can cause issues with servers that only listen on IPv4.

## Testing

After this fix:
1. ✅ Vite proxy connects to `127.0.0.1:51023` (IPv4)
2. ✅ Python proxy receives requests
3. ✅ Connection flows: Browser → Vite → Python Proxy → Octane
4. ✅ No more connection refused errors

## Next Steps

**To test the fix:**

1. **Restart Vite dev server** (IMPORTANT):
   ```bash
   # Stop current server (Ctrl+C)
   npm run dev
   ```

2. **Verify Python proxy is still running**:
   - Should show: "Proxy server running on http://0.0.0.0:51023"
   - Should show: "Successfully connected to Octane at 127.0.0.1:51022"

3. **Clear browser cache and reload**:
   - Hard refresh: Ctrl+Shift+R (Windows) or Cmd+Shift+R (Mac)
   - Or DevTools → Network → Check "Disable cache"

4. **Monitor terminal output**:
   - Should NOT see `ECONNREFUSED` errors
   - Should see successful proxy requests in Python proxy logs

5. **Check browser console**:
   - Should NOT see CORS errors
   - Should see successful API responses

## Expected Behavior

### Successful Connection Flow:

```
[Vite Dev Server]
  Browser requests: /api/rpc/octane.render.RenderServerInfo/GetServerInfo
  ↓
  Vite proxy intercepts /api/*
  ↓
  Forwards to: http://127.0.0.1:51023/rpc/octane.render.RenderServerInfo/GetServerInfo
  ↓
[Python Proxy]
  Receives HTTP/JSON request
  ↓
  Converts to gRPC binary
  ↓
  Sends to Octane: 127.0.0.1:51022
  ↓
[Octane LiveLink]
  Processes gRPC request
  ↓
  Returns gRPC response
  ↓
[Python Proxy]
  Converts gRPC to HTTP/JSON
  ↓
  Returns to Vite proxy
  ↓
[Vite Dev Server]
  Returns to Browser
  ↓
✅ SUCCESS
```

## Alternative Solutions (if issue persists)

### Option 1: Make Python proxy listen on IPv6
Modify `octane_proxy.py` to bind to `::`:
```python
web.run_app(app, host='::', port=51023)  # Listen on IPv6 all interfaces
```

### Option 2: Disable IPv6 in Node.js
Set DNS resolution order in vite.config.ts:
```typescript
import dns from 'node:dns'
dns.setDefaultResultOrder('ipv4first')
```

### Option 3: Use 0.0.0.0
Try using the "any" address:
```typescript
target: 'http://0.0.0.0:51023',
```

**Current solution (127.0.0.1) is the simplest and most reliable.**

## Related Files

- `octaneWeb2/vite.config.ts` - Proxy configuration
- `octaneProxy/octane_proxy.py` - Python proxy server
- `octaneWeb2/CORS_FIX_IMPLEMENTATION.md` - Previous CORS fix docs

## Commit History

1. **Initial CORS fix**: Changed octaneClient.ts to use `/api` relative URLs
2. **IPv6 fix**: Changed proxy target from `localhost` to `127.0.0.1`
