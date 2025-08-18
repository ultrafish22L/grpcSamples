# Node Inspector Optimization Plan

## 🚨 **CRITICAL REQUIREMENT: REAL OCTANE ONLY**

**⚠️ NEVER EVER use mock or simulated data - only real live connection with Octane LiveLink service.**

## 🎯 OBJECTIVE
Optimize Node Inspector to reuse Scene Outliner's cached data instead of redundant tree traversal.

## 🔍 CURRENT INEFFICIENCY
- **Scene Outliner**: Traverses entire tree, stores all node handles/metadata in `this.lastSceneItems`
- **Node Inspector**: Re-traverses tree recursively for each selected node (REDUNDANT!)
- **Result**: Duplicate API calls, slower performance, unnecessary Octane load

## ✅ OPTIMIZED APPROACH

### 1. Data Sharing Architecture
```javascript
// Scene Outliner already has:
this.lastSceneItems = [
    {
        name: "Render target",
        handle: 1000025,
        type: "node", 
        outtype: "NT_RENDERTARGET",
        children: [...]
    },
    // ... all nodes with handles
]
```

### 2. Node Inspector Optimization
```javascript
// BEFORE (inefficient):
async loadAndRenderFullParameterTree(data) {
    // ❌ Re-traverse entire tree
    const parameters = await this.loadNodeParametersRecursively(nodeHandle, 3);
}

// AFTER (optimized):
async loadAndRenderFullParameterTree(data) {
    // ✅ Get cached node data from Scene Outliner
    const nodeData = this.getNodeDataFromCache(data.handle);
    
    // ✅ Only query Octane for parameter VALUES of selected node
    const parameters = await this.loadNodeParameterValues(data.handle, nodeData);
}
```

### 3. Implementation Steps

#### Step 1: Add Scene Data Access
- Add method to access Scene Outliner's cached data
- Create node lookup by handle for O(1) access

#### Step 2: Replace Tree Traversal
- Remove `loadNodeParametersRecursively()` 
- Replace with `loadNodeParameterValues()` that only gets values

#### Step 3: Parameter Value Loading
- Use cached node metadata (type, name, etc.)
- Only make live API calls for parameter values:
  - `ApiNode/pinCount` (once per node)
  - `ApiNode/getPinValueIx` (per parameter)
  - Skip tree traversal entirely

#### Step 4: Event System Integration
- Listen for `sceneDataLoaded` event from Scene Outliner
- Update node cache when scene data changes
- Invalidate cache on scene reload

## 🚀 PERFORMANCE BENEFITS

### Before Optimization:
```
Scene Load: 50+ API calls (tree traversal)
Node Select: 20+ API calls (re-traverse subtree)
Total: 70+ API calls per selection
```

### After Optimization:
```
Scene Load: 50+ API calls (tree traversal) - ONCE
Node Select: 5-10 API calls (parameter values only)
Total: 55+ API calls total, 5-10 per selection
```

### Efficiency Gains:
- **80% reduction** in API calls per node selection
- **Instant** node switching (cached metadata)
- **Reduced** Octane server load
- **Better** user experience (faster response)

## 🔧 IMPLEMENTATION DETAILS

### Cache Structure:
```javascript
this.nodeCache = new Map(); // handle -> nodeData
this.nodeLookup = new Map(); // name -> handle
```

### API Call Pattern:
```javascript
// OLD: Tree traversal + parameter loading
ApiProjectManager/rootNodeGraph → ApiNodeGraph/getOwnedItems → 
ApiItemArray/size → ApiItemArray/get1 → ApiNode/pinCount → 
ApiNode/pinNameIx → ApiNode/pinTypeIx → ... (recursive)

// NEW: Parameter values only
ApiNode/pinCount → ApiNode/getPinValueIx (per parameter)
```

### Error Handling:
- Graceful fallback to full traversal if cache miss
- Cache invalidation on connection errors
- Retry logic for parameter value failures

## 📋 IMPLEMENTATION CHECKLIST

- [ ] Add scene data cache access methods
- [ ] Create node lookup system (handle/name mapping)
- [ ] Replace recursive tree traversal with cached lookup
- [ ] Implement parameter value-only loading
- [ ] Add cache invalidation on scene reload
- [ ] Add error handling and fallback mechanisms
- [ ] Test with various node types and parameter counts
- [ ] Verify performance improvements
- [ ] Update documentation

## 🎯 SUCCESS CRITERIA

1. **Performance**: Node selection responds in <100ms
2. **Efficiency**: <10 API calls per node selection
3. **Reliability**: Graceful fallback if cache unavailable
4. **Compatibility**: Works with all existing node types
5. **Maintainability**: Clean separation of concerns

This optimization will make octaneWeb significantly more responsive and reduce load on the Octane server.