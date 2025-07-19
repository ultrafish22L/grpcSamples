# 🎯 STAGEIT: OCTANE CONNECTION DEFINITIVE PLAN
## Never Figure This Out Again - The Working Pattern

**CREATED**: 2025-07-19  
**PURPOSE**: Document the proven working pattern for Octane connections so I never have to re-figure this out  
**STATUS**: DEFINITIVE - Use this pattern always

---

## 🔥 THE PROVEN WORKING PATTERN

### ✅ WHAT WORKS (html/index.html + proxy/grpc_proxy.py)

**ARCHITECTURE**:
```
Browser (html/index.html) 
    ↓ HTTP/JSON
Proxy (proxy/grpc_proxy.py on port 51023)
    ↓ gRPC 
Octane LiveLink (127.0.0.1:51022 or host.docker.internal:51022)
```

**KEY SUCCESS FACTORS**:

1. **ENFORCED PORT CONFIGURATION** (proxy/grpc_proxy.py lines 27-29):
   ```python
   OCTANE_PORT = 51022  # Octane LiveLink Server (always)
   PROXY_PORT = 51023   # This proxy server (always)
   ```

2. **SIMPLE HTTP-TO-GRPC TRANSLATION**:
   - Browser sends HTTP POST to `http://localhost:51023/livelinkapi.LiveLinkService/GetCamera`
   - Proxy translates to gRPC call to Octane at 127.0.0.1:51022
   - Response comes back as JSON

3. **WORKING CONNECTION PATTERN** (html/index.html):
   ```javascript
   // Server address input defaults to: http://127.0.0.1:51023
   // Connection manager handles the HTTP requests
   this.liveLink = await this.connectionManager.connect(serverAddress);
   ```

4. **PROVEN URL FORMAT**:
   ```
   http://localhost:51023/livelinkapi.LiveLinkService/GetCamera
   http://localhost:51023/octaneapi.ApiProjectManagerService/rootNodeGraph
   ```

---

## ❌ WHAT DOESN'T WORK (My Overcomplication)

### 🚫 FAILED PATTERNS TO AVOID:

1. **Comprehensive Proxy Overengineering**:
   - Creating new proxy formats with `/api` endpoints
   - Parsing service/method from JSON body
   - Adding unnecessary abstraction layers

2. **URL Format Changes**:
   - Changing from `/livelinkapi.Service/method` to `/api` + JSON body
   - Breaking the proven working pattern

3. **Port Configuration Changes**:
   - Using different ports than 51023 (proxy) and 51022 (Octane)
   - Making ports configurable when they should be fixed

4. **Connection Manager Replacement**:
   - Replacing working ConnectionManager with new implementations
   - Changing proven HTTP request patterns

---

## 🎯 STAGEIT IMPLEMENTATION PLAN

### STAGE 1: Use Proven Proxy Pattern
**OBJECTIVE**: Use the working proxy/grpc_proxy.py pattern

**ACTIONS**:
1. ✅ **COPY WORKING PROXY**: Use proxy/grpc_proxy.py as the base
2. ✅ **KEEP PORT 51023**: Never change the proxy port
3. ✅ **KEEP URL FORMAT**: Use `/livelinkapi.Service/method` format
4. ✅ **ADD MISSING SERVICES**: Extend proxy to support ApiProjectManagerService, etc.

**SUCCESS CRITERIA**:
- Proxy runs on port 51023
- Browser can connect to http://localhost:51023
- GetCamera works exactly like html/index.html

### STAGE 2: Extend Working Proxy
**OBJECTIVE**: Add Octane API services to the working proxy

**ACTIONS**:
1. ✅ **ADD OCTANE SERVICES**: Add ApiProjectManagerService, ApiItemService, etc.
2. ✅ **KEEP SAME URL FORMAT**: `/octaneapi.ApiProjectManagerService/rootNodeGraph`
3. ✅ **SAME HTTP TRANSLATION**: HTTP POST → gRPC call → JSON response
4. ✅ **NO ARCHITECTURAL CHANGES**: Just add more service handlers

**SUCCESS CRITERIA**:
- All Octane API calls work with same URL pattern
- No changes to browser connection code
- Scene data loads successfully

### STAGE 3: Update OctaneWeb Client
**OBJECTIVE**: Make OctaneWeb use the proven connection pattern

**ACTIONS**:
1. ✅ **USE WORKING URL FORMAT**: Change from `/api` back to `/octaneapi.Service/method`
2. ✅ **USE WORKING CONNECTION**: Copy ConnectionManager pattern from html/index.html
3. ✅ **SAME HTTP REQUESTS**: POST to specific URLs, not generic `/api`
4. ✅ **NO CUSTOM PARSING**: Let proxy handle service/method parsing

**SUCCESS CRITERIA**:
- OctaneWeb connects exactly like html/index.html
- Scene outliner populates with real Octane data
- All API calls work without 501 errors

---

## 🔧 TECHNICAL IMPLEMENTATION

### WORKING PROXY PATTERN (proxy/grpc_proxy.py):

```python
class LiveLinkProxy:
    def __init__(self, octane_address=f'127.0.0.1:{OCTANE_PORT}'):
        self.octane_address = octane_address
        
    async def handle_grpc_request(self, request):
        # Extract service and method from URL path
        path = request.path
        # /livelinkapi.LiveLinkService/GetCamera → service=LiveLinkService, method=GetCamera
        
        # Create gRPC channel to Octane
        channel = grpc.aio.insecure_channel(self.octane_address)
        
        # Call appropriate gRPC service
        # Return JSON response
```

### WORKING CLIENT PATTERN (html/index.html):

```javascript
class ConnectionManager {
    async connect(serverAddress) {
        // Test connection with simple HTTP POST
        const testUrl = serverAddress + '/livelinkapi.LiveLinkService/GetCamera';
        const response = await fetch(testUrl, {
            method: 'POST',
            headers: { 'Content-Type': 'application/grpc-web+proto' }
        });
        // Return connection object
    }
}
```

### WORKING API CALL PATTERN:

```javascript
// CORRECT - Use specific URL for each service/method
const response = await fetch('http://localhost:51023/octaneapi.ApiProjectManagerService/rootNodeGraph', {
    method: 'POST',
    headers: { 'Content-Type': 'application/grpc-web+proto' },
    body: grpcWebMessage
});

// WRONG - Generic API endpoint with JSON parsing
const response = await fetch('http://localhost:51023/api', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ service: 'ApiProjectManagerService', method: 'rootNodeGraph' })
});
```

---

## 🚨 CRITICAL SUCCESS RULES

### 1. **NEVER CHANGE WORKING PORTS**
- Proxy: ALWAYS port 51023
- Octane: ALWAYS port 51022
- These are hardcoded for consistency

### 2. **NEVER CHANGE WORKING URL FORMAT**
- Use: `/livelinkapi.Service/method` and `/octaneapi.Service/method`
- Don't use: `/api` with JSON body parsing

### 3. **NEVER REPLACE WORKING CONNECTION MANAGER**
- Copy the pattern from html/index.html
- Don't create new connection abstractions

### 4. **ALWAYS TEST WITH WORKING EXAMPLE FIRST**
- Verify html/index.html works
- Then extend the same pattern
- Never start from scratch

### 5. **USE DOCKER NETWORKING CORRECTLY**
- In Docker: `host.docker.internal:51022` for Octane
- Locally: `127.0.0.1:51022` for Octane
- Proxy always binds to `0.0.0.0:51023`

---

## 🎯 VERIFICATION CHECKLIST

### ✅ CONNECTION WORKING:
- [ ] html/index.html connects successfully
- [ ] GetCamera returns real data
- [ ] Proxy logs show successful gRPC calls

### ✅ OCTANE API WORKING:
- [ ] ApiProjectManagerService/rootNodeGraph returns handle
- [ ] ApiItemService/name returns object names
- [ ] Scene outliner populates with real data

### ✅ NO OVERCOMPLICATION:
- [ ] Using proven URL format
- [ ] Using proven port configuration
- [ ] Using proven connection pattern
- [ ] No unnecessary abstractions

---

## 📝 LESSONS LEARNED

### ✅ WHAT WORKS:
1. **Simple HTTP-to-gRPC translation** with URL-based routing
2. **Fixed port configuration** for consistency
3. **Proven connection patterns** from html/index.html
4. **Direct service/method URLs** instead of generic endpoints

### ❌ WHAT FAILS:
1. **Overengineering** the proxy with new formats
2. **Changing working patterns** without understanding why they work
3. **Generic API endpoints** that require custom parsing
4. **Port configuration changes** that break existing integrations

### 🎯 GOLDEN RULE:
**"If html/index.html works, copy its pattern exactly. Don't reinvent."**

---

## 🚀 NEXT ACTIONS

1. **IMMEDIATE**: Stop using comprehensive proxy, revert to proven pattern
2. **EXTEND**: Add Octane API services to working proxy/grpc_proxy.py
3. **UPDATE**: Change OctaneWeb to use proven URL format
4. **VERIFY**: Test that scene outliner populates with real data
5. **DOCUMENT**: Update this plan with any new discoveries

**REMEMBER**: This pattern has worked dozens of times. Trust it. Use it. Don't reinvent it.

---

*"Discipline over cleverness. Evidence over intuition. Focus over completeness."*