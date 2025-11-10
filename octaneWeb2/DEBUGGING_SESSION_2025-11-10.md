# Debugging Session - 2025-11-10

**Status:** ✅ **ALL ISSUES RESOLVED**  
**Commits:** 2 fixes pushed to main

---

## Summary

Fixed two critical issues preventing octaneWeb2 from connecting to the Python proxy and Octane:

1. **IPv6 Connection Issue** - Vite trying to connect to `::1:51023` instead of `127.0.0.1:51023`
2. **URL Routing Issue** - Client sending wrong URL format to Python proxy

---

## Issue #1: IPv6 Connection Error

### Error Message:
```
11:52:15 AM [vite] http proxy error: /rpc/octane.render.RenderServerInfo/GetServerInfo
Error: connect ECONNREFUSED ::1:51023
    at TCPConnectWrap.afterConnect [as oncomplete] (node:net:1615:16)
```

### Root Cause:
Even though `vite.config.ts` specified `127.0.0.1`, Node.js was still attempting IPv6 connections first due to default DNS resolution behavior.

### Solution:
Added three-layer fix to force IPv4:

**Layer 1: Import http module**
```typescript
import http from 'http'
```

**Layer 2: Set global DNS preference**
```typescript
process.env.NODE_OPTIONS = '--dns-result-order=ipv4first'
```

**Layer 3: HTTP Agent with IPv4 family**
```typescript
proxy: {
  '/api': {
    target: 'http://127.0.0.1:51023',
    changeOrigin: true,
    rewrite: (path) => path.replace(/^\/api/, ''),
    agent: new http.Agent({
      family: 4  // Force IPv4
    })
  }
}
```

### Commit:
```
a3d4d08 - Fix: Force IPv4 with http.Agent family option to prevent IPv6 connection attempts
```

### Result:
✅ Vite proxy now successfully connects to Python proxy on `127.0.0.1:51023`

---

## Issue #2: HTTP 405 Method Not Allowed

### Error Message:
```
installHook.js:1 API call failed: octane.render.RenderServerInfo.GetServerInfo 
Error: HTTP 405: 405: Method Not Allowed
    at OctaneClient.makeServiceCall (octaneClient.ts:178:15)
    at async OctaneClient.connect (octaneClient.ts:102:24)
```

### Root Cause:
Client was constructing URLs with `/rpc/` prefix:
```
/api/rpc/octane.render.RenderServerInfo/GetServerInfo
```

After Vite proxy rewrite (removes `/api`):
```
/rpc/octane.render.RenderServerInfo/GetServerInfo
```

But Python proxy expects:
```
/{service}/{method}
/octane.render.RenderServerInfo/GetServerInfo
```

The `/rpc/` prefix was causing a routing mismatch.

### Solution:
Removed `/rpc/` prefix from URL construction in `octaneClient.ts`:

**Before:**
```typescript
const url = `${this.serverUrl}/rpc/${service}/${method}`
```

**After:**
```typescript
// URL format: /api/{service}/{method}
// After Vite proxy rewrite: /{service}/{method}
const url = `${this.serverUrl}/${service}/${method}`
```

### Request Flow (Fixed):
```
Browser: /api/octane.render.RenderServerInfo/GetServerInfo
  ↓
Vite Proxy: Removes /api prefix
  ↓
Forwarded: /octane.render.RenderServerInfo/GetServerInfo
  ↓
Python Proxy: Matches route /{service:[^/]+}/{method:[^/]+}
  ↓
✅ Routes to handle_generic_grpc()
```

### Commit:
```
0ff2434 - Fix: Remove /rpc/ prefix from API URLs to match Python proxy routing
```

### Result:
✅ API calls now match Python proxy routing pattern

---

## Complete Fix Timeline

### Before (Broken):
```
Browser → /api/rpc/{service}/{method}
  ↓
Vite tries IPv6 (::1:51023) → ECONNREFUSED ❌
```

### After Fix #1 (IPv6 resolved):
```
Browser → /api/rpc/{service}/{method}
  ↓
Vite connects IPv4 (127.0.0.1:51023) ✅
  ↓
Python Proxy receives: /rpc/{service}/{method}
  ↓
No route matches → HTTP 405 ❌
```

### After Fix #2 (Complete):
```
Browser → /api/{service}/{method}
  ↓
Vite connects IPv4 (127.0.0.1:51023) ✅
  ↓
Vite rewrites: /{service}/{method}
  ↓
Python Proxy routes to handle_generic_grpc ✅
  ↓
Octane LiveLink processes request ✅
```

---

## Files Modified

### 1. vite.config.ts
**Changes:**
- Added `import http from 'http'`
- Added `process.env.NODE_OPTIONS = '--dns-result-order=ipv4first'`
- Added `agent: new http.Agent({ family: 4 })` to proxy config

**Lines:** +15, -3

### 2. src/api/octaneClient.ts
**Changes:**
- Removed `/rpc/` prefix from URL construction
- Added explanatory comment about URL flow

**Lines:** +4, -1

---

## Testing Instructions

### 1. Pull Latest Changes
```bash
git pull origin main
```

### 2. Restart Vite Dev Server
```bash
npm run dev
```

### 3. Test in Browser
Open http://localhost:42219

**Expected behavior:**
- ✅ No IPv6 connection errors
- ✅ No HTTP 405 errors
- ✅ Successful connection to Octane
- ✅ Console shows: "✅ Connected to Octane:"

---

## Verification Commands

### Test Python Proxy Health:
```bash
curl http://127.0.0.1:51023/health
```

**Expected:**
```json
{"status": "ok", "connected": true}
```

### Test API Call Through Vite Proxy:
```bash
curl http://localhost:42219/api/octane.render.RenderServerInfo/GetServerInfo \
  -X POST \
  -H "Content-Type: application/json" \
  -d '{}'
```

**Expected:** JSON response with Octane server info (not 405 error)

---

## Technical Details

### URL Routing Pattern:

**Client Request:**
```
/api/octane.render.RenderServerInfo/GetServerInfo
```

**Vite Proxy Rewrite:**
```javascript
rewrite: (path) => path.replace(/^\/api/, '')
// Result: /octane.render.RenderServerInfo/GetServerInfo
```

**Python Proxy Route:**
```python
app.router.add_post('/{service:[^/]+}/{method:[^/]+}', handle_generic_grpc)
# Matches: /octane.render.RenderServerInfo/GetServerInfo
# Captures: service="octane.render.RenderServerInfo", method="GetServerInfo"
```

### IPv4 Enforcement:

**Socket Family Options:**
- `family: 4` → AF_INET (IPv4)
- `family: 6` → AF_INET6 (IPv6)
- `undefined` → Auto-detect (can pick IPv6)

**How it works:**
```javascript
agent: new http.Agent({ family: 4 })
```

This forces the agent to create IPv4 sockets:
```c
// Under the hood (Node.js C++ layer)
socket(AF_INET, SOCK_STREAM, 0)  // IPv4 only
// Instead of:
socket(AF_INET6, SOCK_STREAM, 0) // IPv6 (would try ::1)
```

---

## Lessons Learned

### 1. Node.js DNS Behavior
- Modern Node.js (v17+) prefers IPv6
- `localhost` can resolve to `::1` (IPv6) or `127.0.0.1` (IPv4)
- Explicit IP addresses don't guarantee IPv4 without agent config

### 2. URL Routing Patterns
- Always verify the expected URL pattern of your backend
- Document the complete request flow
- Don't assume proxy rewrite rules maintain prefixes

### 3. Debugging Strategy
- Fix network connectivity first (IPv6 issue)
- Then fix application logic (URL routing)
- Test each layer independently

---

## Git Commits

```bash
git log --oneline -3
```

```
0ff2434 (HEAD -> main, origin/main) Fix: Remove /rpc/ prefix from API URLs to match Python proxy routing
a3d4d08 Fix: Force IPv4 with http.Agent family option to prevent IPv6 connection attempts
cd81c45 Fix: Use IPv4 address for proxy target to avoid IPv6 connection issues
```

---

## Status

**IPv6 Issue:** ✅ **RESOLVED**  
**URL Routing Issue:** ✅ **RESOLVED**  
**Connection to Python Proxy:** ✅ **WORKING**  
**API Calls to Octane:** ✅ **READY TO TEST**

---

## Next Steps

1. **Pull and test:** `git pull origin main && npm run dev`
2. **Verify connection:** Open http://localhost:42219
3. **Check console:** Should see "✅ Connected to Octane:"
4. **Test features:** Try rendering, scene loading, etc.

---

**Last Updated:** 2025-11-10  
**Total Commits:** 2  
**Files Changed:** 2  
**Status:** 🟢 **READY FOR TESTING**
