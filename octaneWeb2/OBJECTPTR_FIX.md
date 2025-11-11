# ObjectPtr Fix - 2025-11-10

## Problem Identified

API calls were failing with "invalid pointer type" error because the proxy expects `objectPtr` structure for API methods that operate on Octane objects.

### Error Example
```
Failed to check isGraph: StatusCode.INVALID_ARGUMENT - "invalid pointer type"
```

### Root Cause
octaneWeb2 was sending:
```json
{
  "handle": "1000000"
}
```

But the proxy expects:
```json
{
  "objectPtr": {
    "handle": "1000000",
    "type": 16
  }
}
```

## Solution Implemented

### 1. Import ObjectType Constants
```typescript
import { NodeType, ObjectType } from '../constants/octaneTypes'
```

### 2. Update makeServiceCall to Convert handle → objectPtr
```typescript
// Convert handle to objectPtr if service requires it
// Following octaneWeb pattern: service name maps to ObjectType enum
const requestParams = { ...params }
if (requestParams.handle && service in ObjectType) {
  const objectType = (ObjectType as any)[service]
  requestParams.objectPtr = {
    handle: requestParams.handle,
    type: objectType
  }
  delete requestParams.handle
}
```

### 3. Service to ObjectType Mapping
Based on octaneWeb's pattern, service names directly map to ObjectType enum:

| Service | ObjectType Value | Description |
|---------|-----------------|-------------|
| ApiItem | 16 | Generic Octane item |
| ApiNode | 17 | Scene node |
| ApiRootNodeGraph | 18 | Root node graph |
| ApiNodeGraph | 20 | Node graph |
| ApiItemArray | 31 | Array of items |

## How It Works

When making API calls:

```typescript
// Before (OLD - BROKEN):
await makeServiceCall('ApiItem', 'isGraph', { handle: '1000000' })
// Sent: { handle: '1000000' } ❌

// After (NEW - FIXED):
await makeServiceCall('ApiItem', 'isGraph', { handle: '1000000' })
// Sent: { objectPtr: { handle: '1000000', type: 16 } } ✅
```

The `makeServiceCall` method now:
1. Checks if params contains `handle`
2. Checks if `service` exists in `ObjectType` enum
3. If both true, creates `objectPtr` with handle and type
4. Removes `handle` from params
5. Sends request with `objectPtr` structure

## Expected Behavior

All these API methods should now work correctly:
- ✅ `getRootNodeGraph()` - Get root scene graph
- ✅ `isGraph(handle)` - Check if item is a graph
- ✅ `getOwnedItems(handle)` - Get child items of a graph
- ✅ `getArraySize(handle)` - Get size of item array
- ✅ `getArrayItem(handle, ix)` - Get item from array
- ✅ `getItemName(handle)` - Get item name
- ✅ `getItemOutType(handle)` - Get item output type
- ✅ `getNodeInfo(handle)` - Get node information
- ✅ `getGraphInfo(handle)` - Get graph information

## Testing

### Without Live Octane
The fix can be verified by checking:
1. No TypeScript compilation errors
2. Request format in proxy logs shows `objectPtr` structure
3. No "invalid pointer type" errors when Octane is available

### With Live Octane
Full end-to-end testing requires:
1. Octane running with LiveLink enabled
2. Connect to proxy
3. Load scene tree
4. Verify all nodes display correctly
5. Test selection and expansion

## Files Modified

- `src/api/octaneClient.ts` - Added objectPtr conversion logic

## Status

✅ **FIX IMPLEMENTED** - Ready for testing with live Octane connection
⏳ **PENDING** - Verification with real Octane instance

## Next Steps

1. ✅ Commit changes
2. ⏳ Test with live Octane when available
3. ⏳ Verify scene tree loads correctly
4. ⏳ Test all scene operations work
