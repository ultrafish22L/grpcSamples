# Fix: "Invalid object type for ApiItem" Error in setByAttrID

**Date**: 2025-01-21  
**Issue**: Parameter updates failing with error: `3 INVALID_ARGUMENT: Invalid object type for ApiItem`

---

## Problem

When attempting to update node parameters (e.g., "Orthographic" checkbox), the `ApiItem.setByAttrID` call was failing with:

```
❌ API error: ApiItem.setByAttrID: 3 INVALID_ARGUMENT: Invalid object type for ApiItem
```

### Root Cause

The **server-side proxy** (vite-plugin-octane-grpc.ts) was remapping the `objectPtr` parameter to `item_ref` for `getByAttrID`, but **NOT for `setByAttrID`**.

```typescript
// BEFORE (line 371)
} else if (method === 'getByAttrID' || method === 'getValue') {
  // Some methods use item_ref instead of objectPtr
  params = { item_ref: params.objectPtr, ...params };
  delete params.objectPtr;
}
// setByAttrID was missing from this condition!
```

According to the protobuf definitions, `ApiItem.setByAttrID` expects the parameter name to be `item_ref`, not `objectPtr`. The proxy was sending:

```json
{
  "objectPtr": {"handle": "1000596", "type": 16},
  "attribute_id": 185,
  "expected_type": 2,
  "bool_value": true
}
```

But Octane gRPC expected:

```json
{
  "item_ref": {"handle": "1000596", "type": 16},
  "attribute_id": 185,
  "expected_type": 2,
  "bool_value": true
}
```

---

## Solution

### Fixed Server-Side Proxy

**File**: `vite-plugin-octane-grpc.ts` (line 604)

```typescript
// BEFORE
} else if (method === 'getByAttrID' || method === 'getValue') {
  // Some methods use item_ref instead of objectPtr
  params = { item_ref: params.objectPtr, ...params };
  delete params.objectPtr;
}

// AFTER
} else if (method === 'getByAttrID' || method === 'setByAttrID' || method === 'getValue') {
  // ApiItem methods use item_ref instead of objectPtr
  params = { item_ref: params.objectPtr, ...params };
  delete params.objectPtr;
}
```

### Added Missing Parameter

**File**: `client/src/components/NodeInspector.tsx` (line 202)

Also added `evaluate: false` parameter which was missing (matches octaneWeb behavior):

```typescript
await client.callApi(
  'ApiItem',
  'setByAttrID',
  node.handle,
  {
    attribute_id: AttributeId.A_VALUE,
    expected_type: expectedType,
    [valueField]: formattedValue,
    evaluate: false  // Required parameter from octaneWeb
  }
);
```

---

## Changes Made

**1. vite-plugin-octane-grpc.ts** (line 604):
- Added `setByAttrID` to the list of methods that need `item_ref` remapping

**2. client/src/components/NodeInspector.tsx** (line 202):
- Added `evaluate: false` parameter to `setByAttrID` call

---

## Testing

### Build Status
✅ TypeScript compilation successful  
✅ Vite build successful (375.42 kB bundle)

### Expected Behavior

**Before Fix**:
```
🟢 CLIENT: [LOG] 📝 Setting Orthographic = true
❌ API error: ApiItem.setByAttrID: 3 INVALID_ARGUMENT: Invalid object type for ApiItem
🔴 CLIENT: [ERROR] ❌ Failed to update Orthographic: 3 INVALID_ARGUMENT: Invalid object type for ApiItem
```

**After Fix**:
```
🟢 CLIENT: [LOG] 📝 Setting Orthographic = true
✅ Successfully updated Orthographic
```

---

## Technical Details

### Proto Message Structure

From `apinodesystem_3.proto` (ApiItem service):

```protobuf
message SetByAttrIDRequest {
  ObjectRef item_ref = 1;        // NOT objectPtr!
  int32 attribute_id = 2;
  int32 expected_type = 3;
  bool evaluate = 4;
  // ... value fields
}

message GetByAttrIDRequest {
  ObjectRef item_ref = 1;        // NOT objectPtr!
  int32 attribute_id = 2;
  int32 expected_type = 3;
}
```

### Why This Happens

The client-side `callApi()` function automatically wraps handles in an `objectPtr` structure, which is correct for most gRPC services. However, the `ApiItem` service methods use a different field name (`item_ref`) in their protobuf definitions.

The proxy layer is responsible for this remapping, converting:
- `objectPtr` → `item_ref` (for ApiItem methods)
- `objectPtr` → `nodePinInfoRef` (for ApiNodePinInfoEx methods)

The bug was that `setByAttrID` was missing from the remapping logic.

---

## Key Insight

**You were 100% correct!** The issue was:
1. NOT about using the wrong object type (ApiNode vs ApiItem)
2. NOT about the `evaluate` parameter (though adding it was good practice)
3. **It was about the server-side parameter name remapping**

The objectPtr type should always be `ApiItem` (16) when calling `ApiItem.setByAttrID`, regardless of whether the actual object is an ApiNode or ApiNodeGraph. The inheritance is handled on the Octane side.

---

## Related Files

- `vite-plugin-octane-grpc.ts` - Server-side gRPC proxy with parameter remapping
- `client/src/components/NodeInspector.tsx` - Parameter rendering and editing
- `client/src/services/OctaneClient.ts` - Client-side API wrapper

---

**Status**: ✅ Fixed  
**Build**: ✅ Passing  
**Root Cause**: Server-side parameter name remapping missing for `setByAttrID`  
**Ready for**: Testing with live Octane instance
