# 🔥 CRITICAL PATTERNS - NEVER FORGET AGAIN

## ObjectPtr Type Matching Rule
**FUNDAMENTAL LAW**: ObjectPtr.type MUST match the class of the service being called

### Examples:
- `ApiNodeGraphService.getOwnedItems` → ObjectPtr.type = ApiNodeGraph type ID
- `ApiItemService.name` → ObjectPtr.type = ApiItem type ID  
- `ApiRootNodeGraphService.???` → ObjectPtr.type = 18 (ApiRootNodeGraph)

### Type Mappings (from working proxy):
- Type 18 = ApiRootNodeGraph
- Type ??? = ApiNodeGraph
- Type ??? = ApiItem

## Service Method Patterns:
- **ApiRootNodeGraphService**: Methods for root node graph (type 18)
- **ApiNodeGraphService**: Methods for regular node graphs
- **ApiItemService**: Methods for items/nodes
- **ApiNodeSystemService**: System-level node operations

## Debugging Checklist:
1. ✅ What type is the object? (e.g., type 18 = ApiRootNodeGraph)
2. ✅ What service am I calling? (e.g., ApiNodeGraphService)
3. ✅ Do they match? (NO - type 18 ≠ ApiNodeGraph)
4. ✅ What's the correct service for this type? (ApiRootNodeGraphService)
5. ✅ What methods does that service have?

## Cache Busting Rule:
**ALWAYS** add timestamp to avoid stale code: `?v=${new Date().toISOString().replace(/[-:]/g, '').slice(0, 15)}`

## Real Data Rule:
**NEVER** use mock data. Real data or empty UI only.