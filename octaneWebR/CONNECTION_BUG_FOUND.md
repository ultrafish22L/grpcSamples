# Connection Bug Analysis - 2025-01-20

## 🐛 Critical Bug Found: Incorrect API Parameter in onConnect

### Location
**File**: `client/src/components/NodeGraph/NodeGraphEditorNew.tsx`  
**Line**: 393  
**Function**: `onConnect`

### The Bug
```typescript
// LINE 393 - INCORRECT
const response = await client.callApi('ApiNode', 'connectToIx', targetHandle, {
  pinIdx,
  sourceNode: { handle: sourceHandle, type: 17 },
  evaluate: true,
});
```

**Problem**: Passing `targetHandle` (string like "input-0") instead of `target` (node ID like "1000003")

### Expected Behavior
```typescript
// CORRECT VERSION
const response = await client.callApi('ApiNode', 'connectToIx', target, {
  pinIdx,
  sourceNode: { handle: source, type: 17 },  // Also use 'source' not 'sourceHandle'
  evaluate: true,
});
```

### Impact
- **Connection API calls fail**: The third parameter to `callApi` is the `objectPtr` (target node's handle)
- **Connections don't persist**: Even if edge is added to ReactFlow, Octane doesn't receive valid API call
- **Silent failure**: No error handling checks if API call succeeded

### Root Cause Analysis

Looking at the `onConnect` handler (lines 383-410):

```typescript
const onConnect = useCallback(
  async (connection: Connection) => {
    const { source, target, sourceHandle, targetHandle } = connection;
    
    // Extract pin index from targetHandle (format: "input-0", "input-1", etc.)
    const pinIdx = parseInt(targetHandle?.split('-')[1] || '0', 10);
    
    try {
      console.log('🔌 Connecting nodes:', { source, target, pinIdx });
      
      // ❌ BUG: Using targetHandle instead of target
      const response = await client.callApi('ApiNode', 'connectToIx', targetHandle, {
        pinIdx,
        sourceNode: { handle: sourceHandle, type: 17 },  // ❌ BUG: Using sourceHandle instead of source
        evaluate: true,
      });
      
      console.log('✅ Connection API response:', response);
      
      // ⚠️ No validation of API response before adding edge
      setEdges((eds) => addEdge(connection, eds));
    } catch (error) {
      console.error('❌ Error connecting nodes:', error);
    }
  },
  [client, connectingEdgeRef]
);
```

### Variables in ReactFlow Connection Object

```typescript
interface Connection {
  source: string;        // Source node ID (e.g., "1000002")
  target: string;        // Target node ID (e.g., "1000003")
  sourceHandle: string;  // Source handle ID (e.g., "output-0")
  targetHandle: string;  // Target handle ID (e.g., "input-2")
}
```

### Required Fixes

#### Fix 1: Correct API Parameters
```typescript
const response = await client.callApi('ApiNode', 'connectToIx', target, {
  pinIdx,
  sourceNode: { handle: source, type: 17 },
  evaluate: true,
});
```

#### Fix 2: Add Response Validation
```typescript
if (!response || !response.result) {
  console.error('❌ Connection API call failed:', response);
  return;  // Don't add edge if API failed
}

console.log('✅ Connection successful:', response);
setEdges((eds) => addEdge(connection, eds));
```

### Testing Evidence

**System Status:**
- ✅ Dev server running on port 43929
- ✅ Connected to Octane at host.docker.internal:51022
- ✅ WebSocket active (Callback ID: 952584)
- ✅ Scene tree loaded (teapot.obj, Render target, Camera, etc.)
- ✅ Node Graph Editor displaying 2 nodes

**Observed Behavior:**
- Clicking on input pins triggers connection drag (logs show: "🔌 Connection drag started")
- Connection line color updates correctly based on pin type
- Dragging works (logs show: "🎨 Setting connection line color")
- But actual API call to `connectToIx` likely fails silently due to incorrect parameters

### Recommended Action

**Immediate**: Apply both fixes to `NodeGraphEditorNew.tsx` line 393
**Testing**: After fix, test full workflow:
1. Right-click in Node Graph → Create Node → Geometric Primitive → Sphere
2. Drag Sphere output → Render target Geometry input
3. Verify console logs show successful API response
4. Verify connection persists after refresh
5. Check Octane UI to confirm connection exists

### Related Code

**API Call Signature** (from OctaneClient.ts):
```typescript
async callApi(
  serviceName: string,     // "ApiNode"
  methodName: string,      // "connectToIx"
  objectPtr: any,          // ❗ Target node handle (not targetHandle string)
  params?: any             // { pinIdx, sourceNode, evaluate }
): Promise<any>
```

**connectToIx Proto Definition** (nodesystem.proto):
```protobuf
message ConnectToIx {
  int32 pin_idx = 1;
  ref source_node = 2;
  bool evaluate = 3;
}
```

---

**Status**: 🔴 **CRITICAL BUG** - Prevents pin connections from working  
**Priority**: **HIGH** - Core functionality broken  
**Complexity**: **LOW** - Simple parameter fix (2 lines changed)  
**Risk**: **LOW** - Isolated fix, well-tested API pattern
