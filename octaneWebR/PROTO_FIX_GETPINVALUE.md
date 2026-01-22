# Proto Method Fix: getPinBoolIx → getPinValueByIx

## Issue
```
[ERROR] ApiNode.getPinBoolIx error: Method getPinBoolIx not found in service ApiNode
[ERROR] ❌ Failed to get viewport resolution lock: Method getPinBoolIx not found in service ApiNode
```

## Root Cause
The method `getPinBoolIx` exists ONLY in the base `apinodesystem.proto` file, which is not actually implemented in the gRPC service. Only methods from the numbered proto files (`apinodesystem_1.proto`, `apinodesystem_3.proto`, etc.) are available at runtime.

## Solution

### 1. **Vite Plugin Update** (`vite-plugin-octane-grpc.ts`)
Added parameter transformation for `getPinValueByIx` family of methods:

```typescript
} else if (method === 'getPinValueByIx' || method === 'getPinValueByPinID' || method === 'getPinValueByName') {
  // getPinValueByX methods use item_ref instead of objectPtr (apinodesystem_7.proto)
  params = { item_ref: params.objectPtr, ...params };
  delete params.objectPtr;
}
```

These methods are defined in `apinodesystem_7.proto` and require `item_ref` parameter instead of `objectPtr`.

### 2. **RenderService Update** (`client/src/services/octane/RenderService.ts`)
Changed from the non-existent method to the correct one:

**Before:**
```typescript
const valueResponse = await this.apiService.callApi('ApiNode', 'getPinBoolIx', filmSettingsHandle, { pinIx: attrIndex });
return valueResponse?.result ?? false;
```

**After:**
```typescript
// Get the boolean value using getPinValueByIx (apinodesystem_7.proto)
const valueResponse = await this.apiService.callApi('ApiNode', 'getPinValueByIx', filmSettingsHandle, { index: attrIndex });
return valueResponse?.bool_value ?? false;
```

**Key changes:**
- Method: `getPinBoolIx` → `getPinValueByIx`
- Parameter: `pinIx` → `index`
- Response field: `result` → `bool_value`

## Proto Definition Reference

From `apinodesystem_7.proto`:
```protobuf
message getPinValueByIxRequest {
    ObjectRef item_ref = 1;  // which object (handled by vite plugin transformation)
    uint32 index = 2;        // property index
    PinTypeId expected_type = 3; // optional
}

message getPinValueByXResponse {
    oneof value {
        bool bool_value = 10;
        int32 int_value = 11;
        int32_2 int2_value = 12;
        // ... other types
    }
}

rpc getPinValueByIx(ApiNode.getPinValueByIxRequest) returns (ApiNode.getPinValueByXResponse);
```

## Files Changed
1. `vite-plugin-octane-grpc.ts` - Added parameter transformation for getPinValueByX and setPinValueByX methods
2. `client/src/services/octane/RenderService.ts` - Fixed method calls and response handling for both get and set operations

## Testing
✅ Build successful (0 TypeScript errors)
✅ Dev server starts without errors
✅ No runtime errors in console
✅ API calls execute without "method not found" errors

## Important Rule
**Only use methods from numbered proto files:**
- ✅ `apinodesystem_1.proto` - ApiItemArray
- ✅ `apinodesystem_3.proto` - ApiItem, ApiItemGetter, ApiItemSetter
- ✅ `apinodesystem_5.proto` - ApiNodeArray
- ✅ `apinodesystem_6.proto` - ApiNodeGraph
- ✅ `apinodesystem_7.proto` - ApiNode
- ✅ `apinodesystem_8.proto` - ApiRootNodeGraph
- ❌ `apinodesystem.proto` - NOT IMPLEMENTED (definitions only)
