# OctaneProxy Status: REAL-TIME CALLBACK SYSTEM + GRPC INTEGRATION OPERATIONAL ✅

## 🚨 **CRITICAL REQUIREMENT: REAL OCTANE ONLY**

**⚠️ NEVER EVER use mock or simulated data - only real live connection with Octane LiveLink service.**

## 🎯 BREAKTHROUGH ACHIEVED: Real-Time Callback Infrastructure + gRPC API Integration

**OBJECTIVE**: Implement real-time callback streaming system for OnNewImage callbacks from Octane + Generic gRPC API routing.

**STATUS**: ✅ MAJOR SUCCESS - Complete callback system with 92+ callbacks received, 0 stream errors + Generic gRPC handler for all API services.

This document contains all the critical knowledge needed to understand, debug, and work with the OctaneProxy callback system that provides real-time streaming from Octane to web browsers.

---

## 🎯 **PROXY SYSTEM OVERVIEW**

### **Architecture:**
```
Browser (EventSource) → Proxy Server (Server-Sent Events) → callback_streamer.py → Octane LiveLink (gRPC Callbacks)
```

### **Core Function:**
The proxy provides real-time callback streaming from Octane to web browsers using Server-Sent Events, enabling live render updates and progressive rendering visualization without polling.

### **Key Files:**
- **Main Server**: `octane_proxy.py` - HTTP-to-gRPC translation + callback endpoints + **Generic gRPC API handler**
- **Callback Streamer**: `callback_streamer.py` - Real-time callback streaming with dedicated asyncio thread
- **Generated Protobuf**: `generated/` directory - Python gRPC stubs including callback_pb2_grpc
- **Service Registry**: Built-in dynamic service discovery and stub creation

### **🚀 NEW: Generic gRPC API Integration**
- **URL Pattern**: `/{service}/{method}` - Routes any gRPC service/method call
- **Supported Services**: ApiRenderEngineService, ApiCameraService, ApiSceneService, ApiLiveLinkService
- **Request Format**: JSON POST with parameters in body
- **Response Format**: JSON with success/error status and result data
- **Headers**: Content-Type: application/json, X-Call-Id for request tracking

---

## 🌐 **NETWORKING CONFIGURATION**

### **Automatic Environment Detection:**
```python
def get_octane_address():
    """Auto-detect sandbox vs native networking"""
    # 1. Check explicit environment variable
    if os.getenv('OCTANE_HOST'):
        return os.getenv('OCTANE_HOST')
    
    # 2. Detect sandbox environment (OpenHands, Docker, etc.)
    sandbox_indicators = [
        '/openhands' in os.getcwd(),
        os.getenv('OPENHANDS_WORKSPACE_BASE'),
        os.path.exists('/.dockerenv'),
        os.getenv('CONTAINER'),
        os.getenv('USER') == 'sandbox'
    ]
    
    if any(sandbox_indicators):
        return 'host.docker.internal'  # Docker networking
    else:
        return '127.0.0.1'  # Native networking
```

### **Port Configuration:**
- **Proxy Server**: Port 51023 (HTTP server for browser requests + callback endpoints)
- **Octane LiveLink**: Port 51022 (gRPC server, auto-detected host)
- **Health Check**: `http://localhost:51023/health`
- **Callback Registration**: `http://localhost:51023/render/register-callback`
- **Callback Stream**: `http://localhost:51023/render/stream` (Server-Sent Events)

---

## 🔄 **CALLBACK SYSTEM FLOW**

### **Callback Registration Process:**
```python
async def register_callback(request):
    """Register OnNewImage callback with Octane"""
    
    # 1. Parse callback registration request
    data = await request.json()
    callback_type = data.get('callbackType', 'OnNewImage')
    
    # 2. Create proper callback structure
    callback_request = OnNewImageCallbackT()
    callback_request.callbackSource = 1  # CALLBACK_SOURCE_RENDER_TARGET
    callback_request.callbackId = 1      # Unique callback ID
    
    # 3. Register with Octane via callback_streamer
    success = await callback_streamer.register_callback(callback_request)
    
    # 4. Return registration status
    return web.json_response({'success': success, 'callbackId': 1})
```

### **Real-Time Streaming Process:**
```python
async def stream_callbacks(request):
    """Stream real-time callbacks via Server-Sent Events"""
    
    # 1. Create Server-Sent Events response
    response = web.StreamResponse()
    response.headers['Content-Type'] = 'text/event-stream'
    response.headers['Cache-Control'] = 'no-cache'
    
    # 2. Start streaming callbacks from callback_streamer
    async for callback_data in callback_streamer.get_callback_stream():
        # 3. Format as Server-Sent Event
        event_data = f"data: {json.dumps(callback_data)}\n\n"
        await response.write(event_data.encode())
    
    return response
```

### **Generic gRPC Handler Pattern:**
```python
async def handle_generic_grpc(request):
    """Generic handler for any gRPC service call (URL-based routing)"""
    
    # 1. Parse URL path: /ServiceName/methodName
    path_match = re.match(r'^/(?:octaneapi\.|livelinkapi\.)?([^/]+)/([^/]+)$', path)
    service_name = path_match.group(1)  # e.g., "ApiItem"
    method_name = path_match.group(2)   # e.g., "name"
    
    # 2. Get appropriate gRPC stub from registry
    stub = grpc_registry.get_stub(service_name, proxy.channel)
    
    # 3. Get method from stub
    method = getattr(stub, method_name, None)
    
    # 4. Parse JSON request data
    request_data = await request.json()
    
    # 5. Create gRPC request object
    request_class = grpc_registry.get_request_class(service_name, method_name)
    grpc_request = request_class()
    
    # 6. Populate request fields from JSON
    populate_request_fields(grpc_request, request_data)
    
    # 7. Make gRPC call to Octane
    response = await method(grpc_request)
    
    # 8. Convert response to JSON and return
    return web.json_response({'success': True, 'data': response_dict})
```

### **Service Registry System:**
```python
class GrpcServiceRegistry:
    """Dynamic gRPC service stub registry"""
    
    def get_stub(self, service_name, channel):
        """Get or create gRPC stub for service"""
        if service_name not in self.stubs:
            # Map service name to module (e.g., ApiItem → apinodesystem)
            module_name = self.get_module_name(service_name)
            
            # Import protobuf module
            pb2_grpc = importlib.import_module(f'{module_name}_pb2_grpc')
            
            # Create stub class (e.g., ApiItemServiceStub)
            stub_class = getattr(pb2_grpc, f'{service_name}ServiceStub')
            
            # Create and cache stub instance
            self.stubs[service_name] = stub_class(channel)
        
        return self.stubs[service_name]
```

---

## 🚨 **CRITICAL API METHOD VALIDATION**

### **How to Verify Valid Methods:**
```bash
# Check available methods for a service
grep -n "class ApiItemServiceStub" generated/apinodesystem_pb2_grpc.py -A 50

# Look for method definitions like:
# self.name = channel.unary_unary(...)
# self.outType = channel.unary_unary(...)
```

### **✅ CONFIRMED VALID ApiItem Methods:**
- `destroy` - Destroy the item
- `name` - Get item name
- `position` - Get item position
- `uiOperationFlags` - Get UI operation flags
- `select` - Select the item
- `time` - Get time information
- `outType` - Get item output type
- `persistentId` - Get persistent identifier

### **Service-to-Module Mapping:**
```python
service_map = {
    'ApiNodeGraph': 'apinodesystem',
    'ApiNode': 'apinodesystem', 
    'ApiItem': 'apinodesystem',
    'ApiItemArray': 'apinodesystem',
    'ApiProjectManager': 'apiprojectmanager',
    # ... other mappings
}
```

---

## 🔧 **DEBUGGING TECHNIQUES**

### **Proxy Logging Pattern:**
```
🌐 === GENERIC gRPC REQUEST ===
🌐 Path: /ApiItem/name
🌐 Remote: 127.0.0.1
📤 Service: ApiItem
📤 Method: name
📥 Request data: {"objectPtr": {"handle": "1000002", "type": 16}}
📥 SUCCESS: ApiItem.name
```

### **Error Indicators:**
- **❌ ERROR**: Exception occurred during processing
- **❌ Traceback**: Full Python stack trace
- **No response logged**: Proxy crashed or hung
- **HTTP 404**: Method not found on service
- **Socket closed**: Octane disconnected (normal)

### **Common Debugging Commands:**
```bash
# Check proxy health
curl -s http://localhost:51023/health

# Monitor proxy logs
tail -f /tmp/proxy.log

# Test specific API call
curl -X POST http://localhost:51023/ApiItem/name \
  -H "Content-Type: application/json" \
  -d '{"objectPtr": {"handle": "1000002", "type": 16}}'

# Check if proxy is running
ps aux | grep octane_proxy

# Restart proxy
pkill -f octane_proxy
python octane_proxy.py --host 0.0.0.0 --port 51023 --octane-host 127.0.0.1 --octane-port 51022 &
```

### **Method Validation Process:**
1. **Check Service Exists**: Verify service name in protobuf files
2. **Check Method Exists**: Look for method in ServiceStub class
3. **Check Request Class**: Ensure request message type exists
4. **Test with curl**: Make direct HTTP call to proxy
5. **Monitor Logs**: Watch for success/error messages

---

## 🚀 **STARTUP PROCEDURES**

### **Quick Start (Automatic Environment Detection):**
```bash
cd /workspace/grpcSamples/octaneProxy
pip install --upgrade protobuf  # Fix version mismatch if needed
python octane_proxy.py > /tmp/octane_proxy.log 2>&1 &
```

### **Manual Environment Override:**
```bash
# Development Environment (Sandbox)
python octane_proxy.py --host 0.0.0.0 --port 51023 --octane-host host.docker.internal --octane-port 51022

# Native Environment  
python octane_proxy.py --host 0.0.0.0 --port 51023 --octane-host 127.0.0.1 --octane-port 51022
```

### **Complete Setup Guide:**
See `../octaneWeb/NETWORKING.md` for comprehensive networking setup with troubleshooting.

### **Command Line Arguments:**
- `--host`: Proxy server bind address (default: 0.0.0.0)
- `--port`: Proxy server port (default: 51023)
- `--octane-host`: Octane LiveLink host (auto-detected)
- `--octane-port`: Octane LiveLink port (default: 51022)

---

## 📊 **REQUEST/RESPONSE PATTERNS**

### **Typical Request Format:**
```json
{
  "objectPtr": {
    "handle": "1000002",
    "type": 16
  },
  "index": 0  // for array operations
}
```

### **Typical Response Format:**
```json
{
  "success": true,
  "data": {
    "result": "teapot.obj"  // actual response data
  }
}
```

---

## 🛡️ **ERROR HANDLING**

### **Common Error Types:**
1. **Method Not Found**: HTTP 404, method doesn't exist on service
2. **Service Not Found**: Cannot import protobuf module
3. **Connection Failed**: Cannot connect to Octane LiveLink
4. **Invalid Request**: JSON parsing or field population errors
5. **gRPC Errors**: Octane-side errors (UNAVAILABLE, etc.)

### **Error Recovery Patterns:**
```python
try:
    # Make gRPC call
    response = await method(grpc_request)
    print(f"📥 SUCCESS: {service_name}.{method_name}")
    return success_response
    
except Exception as e:
    print(f"❌ ERROR: {e}")
    print(f"❌ Traceback: {traceback.format_exc()}")
    return error_response
```

### **Graceful Degradation:**
- **Invalid Methods**: Return HTTP 404 with clear error message
- **Connection Loss**: Return HTTP 500 with connection error
- **Octane Unavailable**: Return error but keep proxy running
- **Malformed Requests**: Return HTTP 400 with validation error

---

## 📋 **CRITICAL GOTCHAS**

### **Service Name Mapping:**
- **Problem**: Service names don't always match module names
- **Example**: `ApiItem` maps to `apinodesystem` module, not `apiitem`
- **Solution**: Use the service registry mapping system

### **Handle Type Conversion:**
- **Problem**: Handles must be integers, not strings
- **Example**: `"1000002"` should be converted to `1000002`
- **Solution**: Proxy automatically converts handle fields to integers

### **CORS Configuration:**
- **Problem**: Browsers block requests without proper CORS headers
- **Solution**: Proxy includes comprehensive CORS middleware
- **Headers**: `Access-Control-Allow-Origin: *`, `Access-Control-Allow-Methods`, etc.

---

## 🎯 **SUCCESS INDICATORS**

### **Healthy Proxy Shows:**
- ✅ **Health Check**: `{"status": "ok", "connected": true}`
- ✅ **Request Logs**: `📤 Service: ApiItem`, `📤 Method: name`
- ✅ **Success Logs**: `📥 SUCCESS: ApiItem.name`
- ✅ **Response Data**: Valid JSON with `{"success": true, "data": {...}}`

---

## 📝 **RECENT MAJOR CHANGES**

### **Completed (2025-08-17):**
- ✅ **Real-Time Callback System**: Complete OnNewImage callback streaming with 92+ callbacks received
- ✅ **callback_streamer.py**: Fixed asyncio event loop conflicts with dedicated thread-based streaming
- ✅ **Callback Registration**: Proper OnNewImageCallbackT structure with callbackSource and callbackId fields
- ✅ **Server-Sent Events**: /render/stream endpoint providing real-time callback data to browsers
- ✅ **High-Quality Streaming**: 5000 samples/px, 1024x512 resolution, 2MB per frame, 0 stream errors
- ✅ **gRPC Integration**: Fixed callback_pb2_grpc.StreamCallbackServiceStub imports and usage

### **Architecture Success:**
- **Real-Time Streaming**: Server-Sent Events delivering live Octane callbacks to web browsers
- **Dedicated Threading**: Separate asyncio event loop for callback streaming to prevent conflicts
- **Perfect Performance**: 92+ callbacks with 0 stream errors, full queue utilization (10/10)
- **Callback Registration**: Working OnNewImage callback registration with proper protobuf structures
- **Web Integration**: EventSource connections from CallbackRenderViewport.js working perfectly
- **Live Render Data**: Actual high-quality render images (5000 samples/px) streamed in real-time

---

## 🔧 **CALLBACK SYSTEM DEBUGGING**

### **Callback Registration Verification:**
```bash
# Test callback registration
curl -X POST http://localhost:51023/render/register-callback \
  -H "Content-Type: application/json" \
  -d '{"callbackType": "OnNewImage"}'

# Expected response: {"success": true, "callbackId": 1}
```

### **Callback Streaming Test:**
```bash
# Test Server-Sent Events stream
curl -N http://localhost:51023/render/stream

# Expected: Real-time callback data in SSE format
# data: {"callbackId": 1, "imageData": "...", "width": 1024, "height": 512}
```

### **callback_streamer.py Status:**
```bash
# Check if callback streamer is running
ps aux | grep callback_streamer

# Monitor callback streamer logs
tail -f /tmp/callback_streamer.log

# Look for these success indicators:
# ✅ "Registered OnNewImage callback with ID: 1"
# ✅ "Received callback: 92+ callbacks"
# ✅ "Stream errors: 0"
# ✅ "Queue utilization: 10/10"
```

### **Common Callback Issues:**
1. **asyncio Event Loop Conflicts**: Fixed with dedicated thread-based streaming
2. **Protobuf Import Errors**: Use callback_pb2_grpc.StreamCallbackServiceStub
3. **Missing Host/Port**: Ensure octane_address in _reinitialize_for_thread
4. **URL Configuration**: CallbackRenderViewport must use client.serverUrl

---

## 🔍 **PROTOBUF INVESTIGATION COMMANDS**

### **Find Available Services:**
```bash
find generated/ -name "*_pb2_grpc.py" -exec basename {} \; | sed 's/_pb2_grpc.py//'
```

### **List Methods for a Service:**
```bash
# For ApiItem service
grep -n "self\." generated/apinodesystem_pb2_grpc.py | grep "ApiItemServiceStub" -A 20

# For any service
grep -n "class.*ServiceStub" generated/apinodesystem_pb2_grpc.py
```

### **Check Request/Response Types:**
```bash
# Find message types
grep -n "class.*Request\|class.*Response" generated/apinodesystem_pb2.py
```

### **Verify Service Mapping:**
```bash
# Check which services are in which modules
grep -r "class.*ServiceStub" generated/ | cut -d: -f1 | sort | uniq
```

---

## 🛑 **MANDATORY SERVER MANAGEMENT RULE**

### **CRITICAL REQUIREMENT: Server Lifecycle Management**

**⚠️ EVERY SESSION MUST FOLLOW THIS PATTERN:**

1. **🚀 SESSION START**: Always restart servers fresh at beginning of work
   ```bash
   # Kill any existing servers first
   cd /workspace/grpcSamples
   ps aux | grep -E "(octane_proxy|http.server)" | grep -v grep
   kill [PIDs if any found]
   
   # Start fresh servers
   cd octaneProxy && python octane_proxy.py &
   cd ../octaneWeb && python -m http.server 40281 --bind 0.0.0.0 &
   ```

2. **🛑 SESSION END**: ALWAYS stop servers when work is complete
   ```bash
   # Stop all servers before ending session
   ps aux | grep -E "(octane_proxy|http.server)" | grep -v grep
   kill [all server PIDs]
   ```

### **WHY THIS RULE EXISTS:**
- **Resource Management**: Prevents server process accumulation
- **Clean State**: Ensures fresh start for each session  
- **Port Conflicts**: Avoids port binding conflicts (51023, 40281)
- **Memory Leaks**: Prevents long-running process memory issues
- **Debugging**: Clean server state eliminates stale connection issues

### **ENFORCEMENT:**
- **NEVER** leave servers running between sessions
- **ALWAYS** verify servers are stopped before ending work
- **RESTART** servers at start of each new work session
- **DOCUMENT** server status in session notes

---

This guide provides everything needed to understand, debug, and maintain the OctaneProxy system. Always verify API methods exist before implementing new functionality!