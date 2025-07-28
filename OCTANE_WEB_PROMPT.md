# OCTANE_WEB_PROMPT.md
## Quick Start Guide for OpenHands AI Assistant

This document contains all the critical knowledge needed to quickly understand and work with the OctaneWeb system. Use this to get up to speed fast in new chat sessions.

---

## 🎯 **CURRENT SYSTEM STATE (2025-07-28)**

### **✅ WORKING CONFIGURATION:**
- **Web Server**: Running on port 54290 (http://localhost:54290/)
- **Proxy Server**: `grpc_proxy.py` on port 51023 (http://localhost:51023/)
- **Octane Target**: `host.docker.internal:51022` (sandbox environment)
- **Status**: Both SceneOutliner and NodeGraphEditor display real Octane data
- **No Fallback Code**: All sample/placeholder data removed, shows "no data" messages when disconnected

### **🔧 ACTIVE COMPONENTS:**
- **SceneOutliner**: Shows real items like `Item_1000002 [1000002]` and `Item_1000003 [1000003]`
- **NodeGraphEditor**: Displays scene nodes as actual node boxes on canvas
- **Event System**: Perfect communication via `requestSceneData`/`sceneDataLoaded` events
- **Connection Status**: Real-time connection health with retry functionality

---

## 🌐 **NETWORKING ARCHITECTURE**

### **Sandbox Environment Detection:**
The system auto-detects sandbox environments and adjusts networking accordingly:

```python
def get_octane_address():
    # 1. Check explicit environment variable
    if os.getenv('OCTANE_HOST'):
        return os.getenv('OCTANE_HOST')
    
    # 2. Detect sandbox environment
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

### **Connection Flow:**
```
Browser (localhost:54290) 
    ↓ HTTP/JSON
Proxy Server (localhost:51023) 
    ↓ gRPC 
Octane LiveLink (host.docker.internal:51022)
```

---

## 🔄 **PROXY SERVER SYSTEM**

### **Current Proxy: `grpc_proxy.py`**
- **Location**: `/workspace/grpcSamples/proxy/grpc_proxy.py`
- **Port**: 51023 (NOT 51998 - that causes permission errors)
- **Features**: Generic gRPC routing, comprehensive logging, health checks
- **Start Command**: `python grpc_proxy.py --port 51023 --octane-host host.docker.internal --octane-port 51022`

### **Alternative Proxy: `octane_proxy_comprehensive.py`**
- **Location**: `/workspace/grpcSamples/octaneWeb/octane_proxy_comprehensive.py`
- **Port**: Hardcoded to 51998 (causes Windows permission issues)
- **Status**: Legacy, but still functional for some setups

### **Generic gRPC Call Pattern:**
```javascript
// Frontend makes HTTP POST to: /ServiceName/methodName
fetch('http://localhost:51023/ApiProjectManagerService/rootNodeGraph', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ /* request data */ })
})

// Proxy converts to gRPC call:
// ApiProjectManagerService.rootNodeGraph(request) → Octane
```

---

## 📊 **API CALL SEQUENCES**

### **Scene Data Loading Chain:**
```
1. /ApiProjectManagerService/rootNodeGraph
   → Returns: {result: {handle: 1000000, type: 18}} (ApiRootNodeGraph)

2. /ApiNodeGraphService/getOwnedItems  
   → Input: {objectPtr: {handle: 1000000, type: 20}} (convert 18→20)
   → Returns: {list: {handle: 1000014, type: 31}} (ApiItemArray)

3. /ApiItemArrayService/size
   → Input: {objectPtr: {handle: 1000014, type: 31}}
   → Returns: {result: 2} (number of items)

4. /ApiItemArrayService/get1 (for each index)
   → Input: {objectPtr: {handle: 1000014, type: 31}, index: 0}
   → Returns: {result: {handle: 1000002, type: 16}} (ApiItem)
```

### **Critical Type Mappings:**
- **ApiRootNodeGraph**: 18 → Convert to type 20 for getOwnedItems
- **ApiNodeGraph**: 20 (used in getOwnedItems calls)
- **ApiItemArray**: 31 (returned from getOwnedItems)
- **ApiItem**: 16 (individual scene items)

---

## 🎨 **COMPONENT ARCHITECTURE**

### **SceneOutliner.js:**
- **Real Data Source**: Complete API chain from rootNodeGraph to individual items
- **Data Storage**: `this.lastSceneItems` for re-emission to other components
- **Event Emission**: `sceneDataLoaded` event with real scene data
- **Error Handling**: Shows "⚠️ Octane Not Available" with retry button
- **No Fallback**: Eliminated all placeholder/mock data

### **NodeGraphEditor.js:**
- **Data Source**: Listens for `sceneDataLoaded` events from SceneOutliner
- **Initialization**: Emits `requestSceneData` after 100ms delay to handle timing
- **Real Nodes**: Creates actual node boxes like "scene_1000002" from real data
- **No Data State**: Shows "📊 No Scene Data Available" message on canvas
- **No Samples**: Completely removed `createSampleNodes()` method

### **Event System Communication:**
```javascript
// NodeGraphEditor requests data (handles late initialization)
EventSystem.emit('requestSceneData');

// SceneOutliner re-emits stored data
EventSystem.on('requestSceneData', () => {
    if (this.lastSceneItems.length > 0) {
        EventSystem.emit('sceneDataLoaded', this.lastSceneItems);
    }
});

// NodeGraphEditor receives and displays data
EventSystem.on('sceneDataLoaded', (sceneItems) => {
    this.createRealSceneNodes(sceneItems);
});
```

---

## 🚀 **STARTUP PROCEDURES**

### **Development Environment (Sandbox):**
```bash
# 1. Start proxy server
cd /workspace/grpcSamples/proxy
python grpc_proxy.py --port 51023 --octane-host host.docker.internal --octane-port 51022 &

# 2. Start web server  
cd /workspace/grpcSamples/octaneWeb
python -m http.server 54290 --bind 0.0.0.0

# 3. Access application
# http://localhost:54290/
```

### **Windows Environment:**
```batch
# Use the fixed start_proxy.bat (port 51023, not 51998)
cd octaneWeb
start_proxy.bat

# Or manually:
python octane_proxy_comprehensive.py --port 51023
python -m http.server 8080
```

### **Connection Testing:**
- **Proxy Health**: `http://localhost:51023/health`
- **Web App**: `http://localhost:54290/`
- **Connection Status**: Check footer "OctaneLive: connected/error"

---

## 🔧 **DEBUGGING TECHNIQUES**

### **Connection Issues:**
1. **Check Proxy Logs**: Look for "📤 === CALLING OCTANE ===" messages
2. **Verify Octane**: Ensure LiveLink service running on port 51022
3. **Test Health Endpoint**: `curl http://localhost:51023/health`
4. **Check Browser Console**: Look for fetch errors or CORS issues

### **Component Issues:**
1. **Scene Data**: Check if `sceneDataLoaded` events are firing
2. **Node Graph**: Verify `createRealSceneNodes()` is called with data
3. **Event Timing**: Look for `requestSceneData` → `sceneDataLoaded` flow
4. **API Chain**: Trace rootNodeGraph → getOwnedItems → size → get1 sequence

### **Common Fixes:**
- **Port Conflicts**: Use 51023, not 51998 (permission issues)
- **CORS Errors**: Ensure proxy has proper CORS headers
- **Empty Data**: Check if Octane has actual scene content
- **Timing Issues**: Event system handles component initialization order

---

## 📋 **CRITICAL GOTCHAS**

### **Type Conversion Bug:**
- **Issue**: ApiRootNodeGraph (type 18) must be converted to type 20 for getOwnedItems
- **Fix**: `objectPtr: {handle: rootHandle, type: 20}` not type 18

### **Method Name Mapping:**
- **Issue**: Some methods use different names (get1 → getRequest)
- **Fix**: Proxy handles mapping automatically

### **URL Consistency:**
- **Issue**: Multiple hardcoded URLs caused connection failures
- **Fix**: All components now use port 51023 consistently

### **Windows Permissions:**
- **Issue**: Port 51998 requires admin privileges on Windows
- **Fix**: Use port 51023 which works without admin rights

### **Component Initialization:**
- **Issue**: NodeGraphEditor initialized before SceneOutliner loaded data
- **Fix**: Event system with `requestSceneData` handles timing automatically

---

## 🎯 **SUCCESS INDICATORS**

### **Working System Shows:**
- ✅ **Connection**: Green checkbox, "Connected to Octane" status
- ✅ **Scene Outliner**: Real items like "Item_1000002 [1000002]"
- ✅ **Node Graph**: Actual node boxes with scene data
- ✅ **Footer**: "OctaneLive: connected" status
- ✅ **No Placeholders**: No sample/mock data anywhere

### **Failed System Shows:**
- ❌ **Connection**: Red "Connection Failed" status
- ❌ **Scene Outliner**: "⚠️ Octane Not Available" message
- ❌ **Node Graph**: "📊 No Scene Data Available" message
- ❌ **Footer**: "OctaneLive: error" status

---

## 📝 **RECENT MAJOR CHANGES**

### **Completed (2025-07-28):**
- ✅ **Real Data Integration**: Both components show actual Octane scene data
- ✅ **Event System**: Perfect component communication via events
- ✅ **No Fallback Code**: Removed all sample/placeholder data
- ✅ **Networking Auto-Detection**: Sandbox vs native environment detection
- ✅ **Port Standardization**: All URLs use 51023 consistently
- ✅ **Error Handling**: Clear "no data" messages when disconnected

### **Architecture Decisions:**
- **Generic Proxy**: Uses `/ServiceName/methodName` pattern for all gRPC calls
- **Event-Driven**: Components communicate via EventSystem, not direct calls
- **Real Data Only**: No fallback to sample data, clear error states instead
- **Auto-Detection**: Environment-aware networking configuration

---

## 🚀 **QUICK REPRODUCTION STEPS**

1. **Clone/Access**: Repository at `/workspace/grpcSamples/octaneWeb`
2. **Start Proxy**: `cd ../proxy && python grpc_proxy.py --port 51023 --octane-host host.docker.internal --octane-port 51022 &`
3. **Start Web**: `python -m http.server 54290 --bind 0.0.0.0`
4. **Test**: Open `http://localhost:54290/` and verify real scene data displays
5. **Debug**: Check proxy logs, browser console, and component event flow

**Expected Result**: Scene Outliner shows real items, Node Graph shows scene nodes, both connected to live Octane data.