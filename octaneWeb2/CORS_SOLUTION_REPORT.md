# CORS Solution Report for octaneWeb2

**Date:** 2025-11-10  
**Issue:** Browser CORS error when trying to connect to Octane gRPC service

## Current Error Analysis

### Error Message:
```
Access to fetch at 'http://localhost:51023/rpc/octane.render.RenderServerInfo/GetServerInfo' 
from origin 'http://localhost:42219' has been blocked by CORS policy: 
No 'Access-Control-Allow-Origin' header is present on the requested resource.
```

### What's Happening:
1. **Vite dev server** runs on `http://localhost:42219`
2. **React app** tries to fetch from `http://localhost:51023/rpc/...`
3. **Browser blocks** the request due to different origins (42219 vs 51023)
4. **Octane proxy** is configured in vite.config.ts but the path doesn't match

## Why You CANNOT Eliminate the Proxy

### Technical Reality of gRPC-Web:

**Browsers CANNOT directly talk to gRPC servers** because:
- gRPC uses **HTTP/2 binary framing** which browsers don't expose via fetch/XHR
- gRPC uses **Protocol Buffers binary format** not JSON
- gRPC requires **HTTP/2 trailers** which browsers can't access
- Standard gRPC servers **don't send CORS headers**

### You MUST Have a Translation Layer:

**Option A: Envoy Proxy** (official gRPC-Web solution)
- Separate service that translates gRPC-Web ↔ native gRPC
- Requires Docker/binary installation
- Configuration via YAML files
- Most robust for production

**Option B: Python/Node Custom Proxy** (what you have)
- Translates HTTP/JSON ↔ gRPC binary
- Adds CORS headers
- Can run on same machine
- Good for development

**Option C: Vite Dev Proxy** (simplest for development)
- Built into Vite dev server
- No separate process needed
- Only works in development
- **This is what you should use!**

## Current Setup Analysis

### Your vite.config.ts:
```typescript
server: {
  port: 42219,
  proxy: {
    '/api': {
      target: 'http://localhost:51023',
      changeOrigin: true,
      rewrite: (path) => path.replace(/^\/api/, '')
    }
  }
}
```

### Your octaneClient.ts:
```typescript
constructor(serverUrl: string = 'http://localhost:51023') {
  this.serverUrl = serverUrl
}

async makeServiceCall(service: string, method: string, params: any): Promise<any> {
  const url = `${this.serverUrl}/rpc/${service}/${method}`
  const response = await fetch(url, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(params)
  })
}
```

### The Problem:
❌ **Client makes request to:** `http://localhost:51023/rpc/...` (direct to proxy - CORS blocked)  
✅ **Should make request to:** `/api/rpc/...` (goes through Vite proxy - CORS handled)

## Recommended Solutions

### 🏆 SOLUTION 1: Use Vite Proxy (RECOMMENDED for Development)

**Pros:**
- No separate proxy process needed during development
- Vite handles all CORS automatically
- Simplest setup
- Standard React development pattern

**Cons:**
- Only works in development (production needs real proxy)
- Slightly less flexible than dedicated proxy

**Implementation:**
1. Update `vite.config.ts` to proxy `/rpc` paths
2. Update `octaneClient.ts` to use relative URLs in development
3. Keep Python proxy for production builds

---

### 🔧 SOLUTION 2: Fix Python Proxy CORS (Alternative)

**Pros:**
- Same setup for dev and production
- More control over proxy behavior
- Can test production-like environment locally

**Cons:**
- Need to run separate Python proxy process
- More complex startup
- Extra process to manage

**Implementation:**
1. Ensure Python proxy has proper CORS headers
2. Keep current octaneClient.ts configuration
3. Make sure proxy is always running

---

### 💡 SOLUTION 3: Hybrid Approach (BEST PRACTICE)

**Use Vite proxy in development, Python proxy in production**

**Benefits:**
- ✅ Simple development workflow
- ✅ Production-ready deployment path
- ✅ Environment-specific configuration
- ✅ Standard React best practices

**Implementation:**
1. Configure Vite to proxy `/api` → Python proxy (or direct to Octane)
2. Use environment variable for base URL
3. Development: `VITE_API_BASE=""` (uses relative URLs through Vite)
4. Production: `VITE_API_BASE="http://production-proxy:51023"` (uses Python proxy)

## Detailed Implementation Plans

### Plan A: Quick Fix with Vite Proxy (5 minutes)

**Step 1:** Update `vite.config.ts`:
```typescript
server: {
  port: 42219,
  host: '0.0.0.0',
  cors: true,
  proxy: {
    '/api': {
      target: 'http://localhost:51023',  // Python proxy
      changeOrigin: true,
      rewrite: (path) => path.replace(/^\/api/, '')
    }
  }
}
```

**Step 2:** Update `octaneClient.ts`:
```typescript
constructor(serverUrl: string = '/api') {  // Use relative path
  this.serverUrl = serverUrl
}
```

**Result:** All requests go through Vite → Python Proxy → Octane, CORS handled automatically!

---

### Plan B: Environment-Based Configuration (10 minutes)

**Step 1:** Create `.env.development`:
```
VITE_API_BASE_URL=/api
```

**Step 2:** Create `.env.production`:
```
VITE_API_BASE_URL=http://localhost:51023
```

**Step 3:** Update `octaneClient.ts`:
```typescript
constructor(serverUrl?: string) {
  this.serverUrl = serverUrl || import.meta.env.VITE_API_BASE_URL || '/api'
}
```

**Step 4:** Update `vite.config.ts` (same as Plan A)

**Result:** Automatic dev/prod switching, clean separation of concerns!

---

### Plan C: Direct to Octane (No Python Proxy Needed)

**Only if Python proxy adds no value for your use case**

**Step 1:** Update `vite.config.ts`:
```typescript
server: {
  port: 42219,
  host: '0.0.0.0',
  cors: true,
  proxy: {
    '/rpc': {
      target: 'http://localhost:51022',  // Direct to Octane LiveLink
      changeOrigin: true,
      configure: (proxy) => {
        proxy.on('proxyReq', (proxyReq) => {
          // Add any custom headers needed
          proxyReq.setHeader('Content-Type', 'application/grpc-web+proto')
        })
      }
    }
  }
}
```

**Step 2:** Update `octaneClient.ts`:
```typescript
constructor(serverUrl: string = '') {  // Empty = relative URLs
  this.serverUrl = serverUrl
}
```

**Note:** This might not work if Octane expects gRPC binary format. The Python proxy likely does format translation.

## Recommended Action

### 🎯 I recommend **Plan B** (Environment-Based Configuration)

**Why:**
1. **Clean separation** - dev uses Vite proxy, prod uses Python proxy
2. **Standard pattern** - matches React best practices
3. **Flexible** - easy to change URLs per environment
4. **Production-ready** - works for deployment
5. **DX-friendly** - no extra processes during development

**Next Steps:**
1. Verify Python proxy is working correctly
2. Implement Plan B configuration
3. Test connection in browser
4. Document the setup for team

## Additional Findings

### About Your Python Proxy:
- Located at: `/workspace/grpcSamples/octaneProxy/octane_proxy.py`
- Runs on port: `51023`
- Connects to Octane on: `51022`
- Has CORS support built-in
- Includes callback streaming for real-time rendering

### About Octane LiveLink:
- Native gRPC service on port `51022`
- No CORS headers (it's not a web server)
- Requires proxy for browser access
- Supports full gRPC protocol

## Testing Checklist

After implementing solution:
- [ ] Start Octane with LiveLink enabled
- [ ] Start Python proxy (if using): `cd octaneProxy && python octane_proxy.py`
- [ ] Start Vite dev server: `npm run dev`
- [ ] Open browser to `http://localhost:42219`
- [ ] Open DevTools Network tab
- [ ] Verify requests show `/api/rpc/...` not `http://localhost:51023/rpc/...`
- [ ] Verify 200 OK responses
- [ ] Verify no CORS errors

## References

- [Vite Proxy Documentation](https://vitejs.dev/config/server-options.html#server-proxy)
- [MDN CORS Documentation](https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS)
- [gRPC-Web Documentation](https://grpc.io/docs/platforms/web/basics/)
- [React Environment Variables](https://vitejs.dev/guide/env-and-mode.html)
