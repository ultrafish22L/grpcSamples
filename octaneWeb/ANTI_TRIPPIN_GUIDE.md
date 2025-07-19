# 🚨 ANTI-TRIPPIN GUIDE: How to NOT Go Insane on OctaneWeb

## 🔥 CRITICAL RULE #1: LOOK AT WORKING CODE FIRST
**BEFORE making ANY assumptions, check these working examples:**
- `testGrpcApi/main.cpp` - Working C++ gRPC calls
- `octaneGrpcTest` - Working test patterns  
- `proxy/grpc_proxy.py` - Working proxy implementation
- `html/livelink.js` - Working web client patterns

## 🚨 SYMPTOMS OF TRIPPIN:
- ❌ Making assumptions about API structure without checking working code
- ❌ Overthinking simple pass-through proxy patterns
- ❌ Hardcoding type numbers instead of using dynamic service selection
- ❌ Ignoring existing working implementations
- ❌ Going down rabbit holes instead of following proven patterns

## ✅ ANTI-TRIPPIN PROTOCOL:

### STEP 1: STUDY WORKING CODE
```bash
# ALWAYS start here - see what actually works
cd /workspace/grpcSamples/testGrpcApi
grep -r "getOwnedItems\|buildSceneTree" .

cd /workspace/grpcSamples/proxy  
grep -A10 -B10 "scene\|tree\|children" grpc_proxy.py
```

### STEP 2: FOLLOW PROVEN PATTERNS
- **Proxy = Pure Pass-through**: No type transformations, no hardcoded numbers
- **Client specifies service**: "ApiNodeGraphService" not "ApiRootNodeGraphService"  
- **ObjectPtr = {handle, type}**: Use exact values from working responses
- **Service/Type matching**: ObjectPtr.type must match the service being called

### STEP 3: TEST INCREMENTALLY
```bash
# Test each API call individually with curl
curl -X POST http://localhost:51998/ApiProjectManagerService/rootNodeGraph -d '{}'
curl -X POST http://localhost:51998/ApiNodeGraphService/getOwnedItems -d '{"objectPtr": {"handle": X, "type": Y}}'
```

## 🔥 WORKING PATTERNS FROM EXISTING CODE:

### Pattern 1: Root Node Graph Retrieval
```javascript
// From working code - ApiProjectManagerService.rootNodeGraph returns ObjectRef
const rootResponse = await client.makeGrpcCall('ApiProjectManagerService', 'rootNodeGraph', {});
const objectRef = rootResponse.data.result.result; // {handle: 1000001, type: 18}
```

### Pattern 2: Children Retrieval  
```javascript
// From working code - Use ApiNodeGraphService for node graphs
const childrenResponse = await client.makeGrpcCall('ApiNodeGraphService', 'getOwnedItems', {
    objectPtr: objectRef  // Pass through exactly as received
});
```

### Pattern 3: Name Retrieval
```javascript
// From working code - Use ApiItemService for items
const nameResponse = await client.makeGrpcCall('ApiItemService', 'name', {
    objectPtr: itemRef  // Pass through exactly as received  
});
```

## 🚨 FORBIDDEN ANTI-PATTERNS:

### ❌ NEVER DO THIS:
```javascript
// WRONG - Hardcoded type transformations
if (objectRef.type === 18) {
    objectRef.type = 20; // NEVER transform types
}

// WRONG - Hardcoded service selection  
if (type === 18) use ApiRootNodeGraphService; // WRONG
if (type === 20) use ApiNodeGraphService;     // WRONG
```

### ✅ ALWAYS DO THIS:
```javascript
// RIGHT - Pure pass-through based on working patterns
const service = getServiceForObjectType(objectRef.type); // From working code
const response = await client.makeGrpcCall(service, method, {
    objectPtr: objectRef  // Exact pass-through
});
```

## 🔥 EMERGENCY RESET PROTOCOL:

When you start trippin:
1. **STOP** - Don't make more assumptions
2. **LOOK** - Check working code in testGrpcApi/octaneGrpcTest  
3. **COPY** - Use exact patterns from working implementations
4. **TEST** - Verify each step with curl before building complex logic

## 📋 IMPLEMENTATION NOTES THAT CANNOT BE FORGOTTEN:

### Current Working State:
- ✅ **ApiProjectManagerService.rootNodeGraph**: Returns {handle: 1000001, type: 18}
- ✅ **Bulletproof Proxy**: 7 services registered, pure pass-through working
- ✅ **Scene Outliner**: Shows "Scene" with real Octane data
- ❌ **Children Retrieval**: Need to check working patterns in testGrpcApi

### Next Steps (Based on Working Code):
1. Study `testGrpcApi` for correct service/method combinations
2. Copy exact patterns for getting scene children
3. Test each API call individually before integration
4. Follow proven proxy pass-through patterns

### Critical Reminders:
- **ObjectPtr.type must match service class** - This is fundamental law
- **Proxy is pure pass-through** - No transformations ever
- **Working code exists** - Always check it first
- **User has working Octane instance** - Real data available for testing

## 🎯 SUCCESS CRITERIA:
- Scene outliner shows "Scene" with real children like "Render target" and "teapot.obj"
- All API calls use proven patterns from working code
- No hardcoded types or service mappings
- Pure pass-through proxy with dynamic service selection

---

**Remember: The user started with WORKING CODE. Your job is to extend it, not reinvent it.**