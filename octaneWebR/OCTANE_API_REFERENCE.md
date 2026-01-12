# Octane gRPC API Reference

## ⚠️ CRITICAL: Always Check Proto Files

**Before implementing any API call, ALWAYS verify the method name in proto files:**
- Proto files location: `/grpcSamples/octaneProxy/generated/*_pb2_grpc.py`
- Never assume API method names - verify first!

---

## API Pattern: callApi()

All Octane API calls use this pattern:

```typescript
await client.callApi('ServiceName', 'methodName', handle, parameters);
```

**Example**:
```typescript
// Correct ✅
await this.callApi('ApiItem', 'destroy', nodeHandle, {});

// Wrong ❌ (assumed name without checking proto)
await this.callApi('ApiItem', 'deleteItem', nodeHandle, {}); // NO SUCH METHOD
```

---

## ApiItem Service

**Proto file**: `apinodesystem_3_pb2_grpc.py`  
**Service class**: `ApiItemServiceStub`

### Core Methods

| Method | Description | Parameters | Returns |
|--------|-------------|------------|---------|
| `destroy` | **Delete/destroy a node** | `nodeHandle: number` | `Empty` |
| `name` | Get node name | `nodeHandle: number` | `nameResponse` |
| `setName` | Set node name | `nodeHandle: number, name: string` | `Empty` |
| `position` | Get node position in graph | `nodeHandle: number` | `positionResponse` |
| `setPosition` | Set node position in graph | `nodeHandle: number, x: number, y: number` | `Empty` |
| `select` | Select node in Octane UI | `nodeHandle: number` | `Empty` |
| `time` | Get node time | `nodeHandle: number` | `timeResponse` |
| `outType` | Get node output type | `nodeHandle: number` | `outTypeResponse` |
| `persistentId` | Get persistent ID | `nodeHandle: number` | `persistentIdResponse` |
| `uniqueId` | Get unique ID | `nodeHandle: number` | `uniqueIdResponse` |
| `isGraph` | Check if node is a graph | `nodeHandle: number` | `isGraphResponse` |
| `version` | Get node version | `nodeHandle: number` | `versionResponse` |

### Tree & Cleanup Methods

| Method | Description |
|--------|-------------|
| `collectItemTree` | Collect entire item tree from node |
| `deleteUnconnectedItems` | Delete all unconnected items in scene |
| `switchToFileData` | Switch to file data mode |

### UI Operations

| Method | Description |
|--------|-------------|
| `setUIOperationFlags` | Set UI operation flags (hide, lock, etc.) |
| `uiOperationFlags` | Get current UI operation flags |

---

## Common Mistakes & Corrections

### ❌ Wrong: Assumed Method Names
```typescript
// These DO NOT EXIST - never implemented in proto
await this.callApi('ApiItem', 'deleteItem', handle, {});     // ❌ NO
await this.callApi('ApiItem', 'delete', handle, {});         // ❌ NO
await this.callApi('ApiItem', 'removeNode', handle, {});     // ❌ NO
```

### ✅ Correct: Verified Proto Methods
```typescript
// CORRECT - verified in apinodesystem_3_pb2_grpc.py
await this.callApi('ApiItem', 'destroy', handle, {});        // ✅ YES
```

---

## ApiItemArray Service

**Proto file**: `apinodesystem_1_pb2_grpc.py`  
**Service class**: `ApiItemArrayServiceStub`

### Methods

| Method | Description | Parameters | Returns |
|--------|-------------|------------|---------|
| `size` | Get array size | `arrayHandle: number` | `number` |
| `get` | Get item at index | `arrayHandle: number, index: number` | `itemHandle` |
| `set` | Set item at index | `arrayHandle: number, index: number, itemHandle: number` | `Empty` |
| `append` | Append item to array | `arrayHandle: number, itemHandle: number` | `Empty` |

---

## ApiGraph Service

**Proto file**: `apinodesystem_X_pb2_grpc.py` (exact number TBD - check proto files)

### Methods

| Method | Description | Parameters | Returns |
|--------|-------------|------------|---------|
| `getOwnedItems` | Get all items owned by graph | `graphHandle: number` | `arrayHandle` |
| `createNode` | Create new node in graph | `graphHandle: number, nodeType: string` | `nodeHandle` |
| `connect` | Connect two nodes | `sourceHandle: number, targetHandle: number, pinIndex: number` | `Empty` |
| `disconnect` | Disconnect nodes | `sourceHandle: number, targetHandle: number, pinIndex: number` | `Empty` |

---

## How to Find API Methods

### Step 1: Locate Proto File
```bash
cd /grpcSamples/octaneProxy/generated
ls -la *pb2_grpc.py | grep -i "item\|graph\|scene"
```

### Step 2: Check Service Class
```bash
grep -A 50 "class ApiItemServiceStub" apinodesystem_3_pb2_grpc.py
```

### Step 3: Extract Method Names
Look for patterns like:
```python
self.destroy = channel.unary_unary(
    '/octaneapi.ApiItemService/destroy',
    request_serializer=apinodesystem__3__pb2.ApiItem.destroyRequest.SerializeToString,
    response_deserializer=google_dot_protobuf_dot_empty__pb2.Empty.FromString,
)
```

**Method name**: `destroy` (first line)

---

## Implementation Pattern

### TypeScript Client Side
```typescript
// In OctaneClient.ts
async deleteNode(nodeHandle: string): Promise<boolean> {
  const handleNum = Number(nodeHandle);
  
  // ALWAYS CHECK PROTO FIRST!
  // Proto file: apinodesystem_3_pb2_grpc.py
  // Service: ApiItemServiceStub
  // Method: self.destroy
  await this.callApi('ApiItem', 'destroy', handleNum, {});
  
  return true;
}
```

### Python Proxy Side
```python
# In octane_proxy.py
stub = ApiItemServiceStub(channel)

# Proto method: self.destroy
request = apinodesystem_3_pb2.ApiItem.destroyRequest()
request.handle = node_handle
response = await stub.destroy(request)
```

---

## Proto File Organization

**Location**: `/grpcSamples/octaneProxy/generated/`

| Proto File | Service | Purpose |
|------------|---------|---------|
| `apinodesystem_1_pb2_grpc.py` | ApiItemArray | Array operations |
| `apinodesystem_3_pb2_grpc.py` | **ApiItem** | **Node operations (destroy, name, position, etc.)** |
| `apinodesystem_8_pb2_grpc.py` | ApiGraph | Graph operations |
| `apisceneoutliner_pb2_grpc.py` | ApiSceneOutliner | Scene tree operations |
| `apirenderview_pb2_grpc.py` | ApiRenderView | Render view operations |

---

## Development Workflow

### ✅ CORRECT Workflow
1. **Identify required operation** (e.g., "delete node")
2. **Find proto file** (`grep -r "class Api" generated/*.py`)
3. **Check service methods** (read proto class definition)
4. **Verify method name** (e.g., `destroy` not `deleteItem`)
5. **Implement with correct name**

### ❌ WRONG Workflow
1. Assume method name (e.g., "deleteItem sounds right")
2. Implement without checking
3. **API call fails at runtime** ⚠️
4. Debug and discover correct name
5. Waste time refactoring

---

## Key Takeaways

1. **Never assume API method names** - always verify in proto files
2. **Proto files are source of truth** - not documentation or guesses
3. **Common patterns don't always apply** - e.g., `destroy` not `delete`
4. **Check proto first, implement second** - saves debugging time
5. **Document verified methods** - help future developers

---

## Quick Reference Commands

### Find all proto services
```bash
cd /grpcSamples/octaneProxy/generated
grep -h "class.*ServiceStub" *_grpc.py | sort
```

### Find methods in a service
```bash
grep -A 100 "class ApiItemServiceStub" apinodesystem_3_pb2_grpc.py | grep "self\."
```

### Search for a specific method
```bash
grep -r "def destroy\|self.destroy" generated/*_grpc.py
```

---

**Last Updated**: 2025-01-19  
**Status**: Active reference - update as new APIs discovered
