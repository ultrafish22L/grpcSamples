# ObjectPtr Type Conversion Guide - CRITICAL DEBUGGING REFERENCE

## 🔥 THE MOST IMPORTANT OCTANE API DEBUGGING INSIGHT

**⚠️ CRITICAL**: When calling different Octane API services with ObjectPtr, you MUST convert the type field to match the target service, even if the handle stays the same.

## The Problem That Causes Hours of Debugging

### ❌ WRONG - This Always Fails
```python
# Get an object from one service
root_response = await project_stub.rootNodeGraph(empty_request)
object_ref = root_response.result  # type=18 (ApiRootNodeGraph), handle=1000000

# Try to use it with another service - FAILS!
request.objectPtr.handle = object_ref.handle  # 1000000 ✓
request.objectPtr.type = object_ref.type      # 18 (ApiRootNodeGraph) ❌
response = await item_stub.name(request)      # "invalid pointer type" ERROR!
```

### ✅ CORRECT - This Always Works
```python
# Get an object from one service
root_response = await project_stub.rootNodeGraph(empty_request)
object_ref = root_response.result  # type=18 (ApiRootNodeGraph), handle=1000000

# Convert type to match target service - WORKS!
request.objectPtr.handle = object_ref.handle  # 1000000 ✓
request.objectPtr.type = 16                   # ApiItem for ApiItemService ✓
response = await item_stub.name(request)      # SUCCESS! Returns "Scene"
```

## ObjectType Enum Reference (from common.proto)

```proto
enum ObjectType {
    ApiFileName = 0;
    ApiGeometryExporter = 1;
    ApiGuiComponent = 2;
    MetaData = 3;
    ApiImageBuffer = 4;
    ImageType = 5;
    LayerInfo = 6;
    ApiAttributeInfo = 7;
    ApiOcioConfig = 8;
    ApiOctaneModuleInfo = 9;
    ApiOutputColorSpaceInfo = 10;
    ApiSharedSurface = 11;
    ImageExportSettings = 12;
    RenderPassExport = 13;
    RenderResultStatistics = 14;
    ReferencePackageExportSettings = 15;
    ApiItem = 16;                    // ← Use for ApiItemService calls
    ApiNode = 17;                    // ← Use for ApiNodeService calls
    ApiRootNodeGraph = 18;           // ← Use for root node graph operations
    ApiReferenceGraph = 19;
    ApiNodeGraph = 20;               // ← Use for node graph operations
    AnimationTimeTransform = 21;
    ApiAnimationTimeTransform = 22;
    ApiLinearTimeTransform = 23;
    SocketAddress = 24;
    TimeSpanT = 25;
    FrameRangeT = 26;
    ApiCustomCurveEditorController = 27;
    DBCategoryArray = 28;
    DBMaterialArray = 29;
    ImageInfo = 30;
    ApiItemArray = 31;
    Package = 32;
    Category = 33;
    ApiNodeArray = 34;
    ApiOcioConfigLoader = 35;
    ApiOcioContextManager = 36;
    ApiPackage = 37;
    ApiRenderImage = 38;
    ApiSceneExporter = 39;
    VdbGridInfo = 40;
    VdbInfo = 41;
    ApiMainWindow = 42;
    ApiProjectWorkspace = 43;
    ApiNodePinInfo = 44;
    ApiCompatibilityModeInfo = 45;
    ApiCompatibilityModeInfoSet = 46;
    ApiNodeInspector = 47;
    ApiRenderView = 48;
}
```

## Service-to-Type Mapping

| Service | Required ObjectPtr Type | Enum Value |
|---------|------------------------|------------|
| ApiItemService | ApiItem | 16 |
| ApiNodeService | ApiNode | 17 |
| ApiRootNodeGraphService | ApiRootNodeGraph | 18 |
| ApiNodeGraphService | ApiNodeGraph | 20 |
| ApiProjectManagerService | (varies by method) | (varies) |

## Why This Happens - The Technical Explanation

Octane's gRPC API uses **polymorphic object handles**. This means:

1. **One Object, Multiple Interfaces**: The same object (handle=1000000) can be accessed through different service interfaces
2. **Type Field = Interface Selector**: The type field tells the API which interface you want to use
3. **Service Validation**: Each service validates that the ObjectPtr type matches what it expects
4. **Polymorphism in Action**: This is object-oriented polymorphism implemented at the gRPC protocol level

## Real-World Example

```python
# Step 1: Get root node graph (returns ApiRootNodeGraph type)
root_response = await project_stub.rootNodeGraph(empty_request)
print(f"Root object: handle={root_response.result.handle}, type={root_response.result.type}")
# Output: Root object: handle=1000000, type=ApiRootNodeGraph

# Step 2: Get name using ApiItemService (requires ApiItem type)
request = apinodesystem_pb2.ApiItem.nameRequest()
request.objectPtr.handle = root_response.result.handle  # Same handle
request.objectPtr.type = 16  # ApiItem type (NOT ApiRootNodeGraph!)
name_response = await item_stub.name(request)
print(f"Name: {name_response.result}")
# Output: Name: Scene
```

## Common Debugging Scenarios

### Scenario 1: "invalid pointer type" Error
**Symptom**: gRPC call fails with `INVALID_ARGUMENT: invalid pointer type`
**Cause**: ObjectPtr type doesn't match the target service
**Fix**: Change `request.objectPtr.type` to match the service (see table above)

### Scenario 2: Object Handle is Valid But Call Fails
**Symptom**: You know the object exists (got it from another call) but service call fails
**Cause**: Type conversion not performed
**Fix**: Don't copy the original type, use the type required by the target service

### Scenario 3: Working in One Language But Not Another
**Symptom**: C++ code works but Python/JavaScript fails (or vice versa)
**Cause**: One implementation does type conversion, the other doesn't
**Fix**: Ensure all implementations perform proper type conversion

## Code Templates

### Python Template
```python
def call_api_item_service(object_ref, method_name):
    """Template for calling ApiItemService methods"""
    request = getattr(apinodesystem_pb2.ApiItem, f"{method_name}Request")()
    request.objectPtr.handle = object_ref.handle
    request.objectPtr.type = 16  # Always ApiItem for ApiItemService
    return request
```

### JavaScript Template
```javascript
function createApiItemRequest(objectRef, methodName) {
    return {
        objectPtr: {
            handle: objectRef.handle,
            type: 16  // Always ApiItem for ApiItemService
        }
    };
}
```

### C++ Template
```cpp
template<typename RequestType>
RequestType createApiItemRequest(const ObjectRef& objectRef) {
    RequestType request;
    request.mutable_objectptr()->set_handle(objectRef.handle());
    request.mutable_objectptr()->set_type(16);  // ApiItem
    return request;
}
```

## Testing Your Understanding

If you can answer these questions correctly, you understand ObjectPtr type conversion:

1. **Q**: You get an object with type=18 from rootNodeGraph(). What type should you use to call ApiItemService.name()?
   **A**: 16 (ApiItem)

2. **Q**: Why can't you just copy the original object's type?
   **A**: Because the type field specifies which service interface to use, not the object's actual type

3. **Q**: What happens if you use the wrong type?
   **A**: "invalid pointer type" gRPC error

4. **Q**: Can the same handle be used with different service types?
   **A**: Yes! That's the whole point - polymorphic object access

## Remember This Forever

**The ObjectPtr type field is NOT the object's type - it's the SERVICE INTERFACE type you want to use!**

This single insight will save you hours of debugging Octane API integration issues.