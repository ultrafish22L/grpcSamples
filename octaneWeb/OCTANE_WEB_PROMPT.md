# OCTANE_WEB_PROMPT.md
## Quick Start Guide for OpenHands AI Assistant

This document contains all the critical knowledge needed to quickly understand and work with the OctaneWeb system. Use this to get up to speed fast in new chat sessions.

---

## 🎯 **CURRENT SYSTEM STATE (2025-07-28)**

### **✅ WORKING CONFIGURATION:**
- **Web Server**: Running on port 8080 (http://localhost:8080/)
- **Proxy Server**: `octaneProxy/octane_proxy.py` on port 51023 (http://localhost:51023/)
- **Octane Target**: `host.docker.internal:51022` (sandbox environment)
- **Status**: Both SceneOutliner and NodeGraphEditor display real Octane data
- **No Fallback Code**: All sample/placeholder data removed, shows "no data" messages when disconnected

### **🔧 ACTIVE COMPONENTS:**
- **SceneOutliner**: Shows real items like `RenderTarget` and `teapot.obj`
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
Browser (localhost:8080) 
    ↓ HTTP/JSON
Proxy Server (localhost:51023) 
    ↓ gRPC 
Octane LiveLink (host.docker.internal:51022)
```

---

## 🔄 **PROXY SERVER SYSTEM**

### ** Proxy: `octane_proxy.py`**
- **Location**: `/workspace/grpcSamples/octaneProxy/octane_proxy.py`
- **Port**: Hardcoded to 51023 for now

### **Generic gRPC Call Pattern:**
```javascript
// Frontend makes HTTP POST to: /ServiceName/methodName
fetch('http://localhost:51023/ApiProjectManager/rootNodeGraph', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ /* request data */ })
})

// Proxy converts to gRPC call:
// ApiProjectManager.rootNodeGraph(request) → Octane
```

---

## 📊 **API CALL SEQUENCES**

### **Scene Data Loading Chain and Critical Type Mappings:**
```
1. /ApiProjectManager/rootNodeGraph
   → Returns: {result: {handle: 1000000, type: octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph}}

2. /ApiNodeGraph/getOwnedItems  
   → Input: {objectPtr: {handle: 1000000, type: 20}} (convert to base class type: octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiRootNodeGraph->octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNodeGraph)
   → Returns: {list: {handle: 1000014, type: octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItemArray}}

3. /ApiItemArray/size
   → Input: {objectPtr: {handle: 1000014, type: octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItemArray}}
   → Returns: {result: 2} (number of items)

4. /ApiItemArray/get1 (for each index)
   → Input: {objectPtr: {handle: 1000014, type: octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItemArray}, index: 0}
   → Returns: {result: {handle: 1000002, type: octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem}}
```

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
cd /workspace/grpcSamples/octaneProxy
python octane_proxy.py --port 51023 --octane-host host.docker.internal --octane-port 51022 &

# 2. Start web server  
cd /workspace/grpcSamples/octaneWeb
python -m http.server 8080 --bind 0.0.0.0

# 3. Access application
# http://localhost:8080/
```

### **Windows Environment:**
```batch
# Use the fixed start_proxy.bat (port 51023)
cd octaneWeb
start_proxy.bat
```

### **Connection Testing:**
- **Proxy Health**: `http://localhost:51023/health`
- **Web App**: `http://localhost:8080/`
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
- **CORS Errors**: Ensure proxy has proper CORS headers
- **Empty Data**: Check if Octane has actual scene content
- **Timing Issues**: Event system handles component initialization order

---

## 📋 **CRITICAL GOTCHAS**

### **Method Name Mapping:**
- **Issue**: Some methods use different names (get1 → getRequest)
- **Fix**: Proxy handles mapping automatically

### **URL Consistency:**
- **Issue**: Multiple hardcoded URLs caused connection failures
- **Fix**: All components now use port 51023 consistently

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
