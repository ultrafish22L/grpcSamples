# OCTANE_PROXY_PROMPT.md
## HTTP-to-gRPC Proxy Server Guide for OpenHands AI Assistant

This document contains all the critical knowledge needed to understand, debug, and work with the OctaneProxy system that bridges web browsers to Octane's gRPC LiveLink service.

---

## 🎯 **PROXY SYSTEM OVERVIEW**

### **Architecture:**
```
Browser (HTTP/JSON) → Proxy Server (HTTP-to-gRPC) → Octane LiveLink (gRPC)
```

### **Core Function:**
The proxy translates HTTP POST requests with JSON payloads into native gRPC calls to Octane's LiveLink service, enabling web browsers to communicate with Octane without requiring gRPC-Web libraries.

### **Key Files:**
- **Main Server**: `octane_proxy.py` - The core HTTP-to-gRPC translation server
- **Generated Protobuf**: `generated/` directory - Python gRPC stubs and message classes
- **Service Registry**: Built-in dynamic service discovery and stub creation

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
- **Proxy Server**: Port 51023 (HTTP server for browser requests)
- **Octane LiveLink**: Port 51022 (gRPC server, auto-detected host)
- **Health Check**: `http://localhost:51023/health`

---

## 🔄 **REQUEST PROCESSING FLOW**

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

### **❌ INVALID Methods (CAUSE CRASHES):**
- `superclass` - **DOES NOT EXIST** in ApiItemServiceStub
- Any method not defined in the protobuf service definition

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

### **Development Environment (Sandbox):**
```bash
cd /workspace/grpcSamples/octaneProxy
python octane_proxy.py --host 0.0.0.0 --port 51023 --octane-host host.docker.internal --octane-port 51022 > /tmp/proxy.log 2>&1 &
```

### **Native Environment:**
```bash
cd octaneProxy
python octane_proxy.py --host 0.0.0.0 --port 51023 --octane-host 127.0.0.1 --octane-port 51022
```

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

### **Error Response Format:**
```json
{
  "success": false,
  "error": "Method superclass not found on ApiItem"
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

### **🚨 INVALID METHOD CALLS (MAJOR ISSUE):**
- **Problem**: Calling non-existent methods crashes the proxy
- **Example**: `ApiItem/superclass` returns HTTP 404 and may crash proxy
- **Solution**: Always validate methods exist in protobuf definitions
- **Prevention**: Use method validation before implementing new API calls

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

### **Failed Proxy Shows:**
- ❌ **Health Check**: `{"status": "ok", "connected": false}`
- ❌ **Error Logs**: `❌ ERROR: Method superclass not found`
- ❌ **Traceback**: Full Python exception stack trace
- ❌ **No Response**: Request logged but no response (proxy crashed)

---

## 📝 **RECENT MAJOR CHANGES**

### **Completed (2025-07-29):**
- ✅ **Crash Analysis**: Identified invalid `ApiItem/superclass` method as crash source
- ✅ **Method Validation**: Verified all methods against protobuf definitions
- ✅ **Error Handling**: Improved error messages and logging
- ✅ **Stability**: Fixed proxy crashes from invalid method calls

### **Architecture Decisions:**
- **Generic Handler**: Single handler for all gRPC services using URL routing
- **Dynamic Registry**: Runtime service discovery and stub creation
- **Comprehensive Logging**: Detailed request/response logging with emoji indicators
- **Auto-Detection**: Environment-aware Octane host detection
- **Error Resilience**: Graceful handling of invalid requests and connection failures

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

This guide provides everything needed to understand, debug, and maintain the OctaneProxy system. Always verify API methods exist before implementing new functionality!