# OctaneWebR - React/TypeScript Port Mission Prompt (IMPROVED)

## 🎯 Mission Overview
Port the **octaneWeb** project from vanilla JavaScript to a modern React+TypeScript application with **Node.js direct gRPC communication** (replacing the Python proxy). The result must be a pixel-perfect reproduction with identical functionality and user experience.

## 📋 Critical Requirements

### 1. Architecture Changes
- **UI Layer**: Vanilla JavaScript → React 18 + TypeScript
- **Communication Layer**: Python HTTP proxy → Node.js native gRPC client (@grpc/grpc-js)
- **Protocol Handling**: Keep exact same gRPC API calls and message structures
- **No Functionality Loss**: Every feature must work identically

### 2. UI/UX Fidelity (EXACT MATCH)
The React app must be **visually identical** to octaneWeb:

#### Layout Structure
- 4-panel layout: Scene Outliner (left) | Render Viewport (top-right) | Node Graph Editor (middle-right) | Node Inspector (right)
- Top menu bar: File, Edit, Script, Module, Cloud, Window, Help
- Top-right status bar: Connection type selector, connect/disconnect toggle, status LED
- Bottom status bar: Status text, app name, Octane connection info

#### Critical UI Components
1. **Scene Outliner** (`octaneWeb/js/components/SceneOutliner.js`)
   - Hierarchical tree view with expand/collapse arrows
   - Node icons based on type
   - Visibility toggles (eye icons)
   - Three tabs: Scene, Link, Local
   - Search input field
   - Refresh button

2. **Render Viewport** (`octaneWeb/js/components/CallbackRenderViewport.js`)
   - Real-time HDR/LDR image display using callbacks
   - Mouse drag for camera position synchronization
   - Canvas-based rendering with proper buffer handling

3. **Node Graph Editor** (`octaneWeb/js/components/NodeGraphEditor.js`)
   - Visual node creation and editing
   - Right-click context menus
   - Hierarchical node types
   - Zoom/pan controls

4. **Node Inspector** (`octaneWeb/js/components/NodeInspector.js`)
   - Dynamic form generation based on node parameters
   - Real-time parameter editing
   - Type-specific input controls

#### CSS Preservation
**CRITICAL**: The CSS in octaneWeb has significant unused code. You must:
1. Examine how each component **actually builds its DOM** programmatically:
   - `NodeInspector.js` - See `renderParameter()` and `createControl()` methods
   - `GenericNodeRenderer.js` - See how node elements are constructed
   - `SceneOutlinerSync.js` - See `buildTreeElement()` method
2. Extract **only the CSS classes that are actually applied** by these methods
3. Ignore unused CSS rules that don't correspond to programmatically created elements
4. Preserve the exact visual styling (colors, spacing, borders, fonts)

### 3. gRPC Communication Architecture

#### Understanding ObjectRef Protocol
**CRITICAL**: Octane's gRPC API uses `ObjectRef` structures, not plain strings:

```protobuf
message ObjectRef {
    uint64 handle = 1;       // 64-bit pointer reference
    ObjectType type = 2;     // Enum identifying object type
}
```

**Example API Flow**:
```typescript
// ❌ WRONG - Python proxy hid this complexity
const handle = await getRootNodeGraph();  // Returns string "1000000"
await getOwnedItems(handle);              // Sends string - FAILS

// ✅ CORRECT - Node.js direct gRPC
const rootGraph = await getRootNodeGraph();  // Returns {handle: "1000000", type: "ApiRootNodeGraph"}
await getOwnedItems(rootGraph);              // Sends ObjectRef - WORKS
```

#### Node.js gRPC Implementation Strategy
The Python proxy (`octaneProxy/octane_proxy.py`) handles special cases dynamically. You must replicate this logic:

1. **Dynamic Field Population** (see `recurse_attr()` in octane_proxy.py line 648):
   - The proxy examines protobuf descriptors to find correct field names
   - Example: `objectPtr` parameter maps to different fields depending on request type
   - Special cases: `nodePinInfoRef` (GetNodePinInfoRequest), `item_ref` (getValueByIDRequest)

2. **Request Class Resolution** (see `grpc_registry.py`):
   - Each gRPC method requires a specific request message class
   - Example: `ApiNodeGraph.getOwnedItems` → `getOwnedItemsRequest`
   - You must dynamically instantiate the correct request type

3. **Response Handling**:
   - Use `MessageToDict()` equivalent to convert protobuf to JSON
   - Preserve field names (not camelCase conversion)
   - Handle nested ObjectRef structures

#### Proto File Loading Strategy
Load these specific proto files (in order):
```
1. common.proto           # ObjectRef, basic types
2. livelink.proto         # LiveLink service
3. apiprojectmanager.proto # Project/scene management
4. apinodesystem_3.proto  # ApiItem service
5. apinodesystem_6.proto  # ApiNodeGraph service  
6. apinodesystem_7.proto  # ApiNode service
7. apiitemarray.proto     # ApiItemArray service
```

**Why split files?** `apinodesystem.proto` is split into parts 1-7 to avoid naming conflicts. Load only parts 3, 6, 7 for required services.

### 4. Core Functionality to Preserve

#### Scene Loading Algorithm (`OctaneWebClient.js::syncScene()`)
This is the **heart of octaneWeb**. Preserve this exact logic:

```javascript
async syncScene() {
    // 1. Get root node graph handle
    const rootGraphPtr = await this.getRootNodeGraph();
    
    // 2. Recursively build tree
    return await this.syncSceneRecurse(rootGraphPtr);
}

async syncSceneRecurse(graphPtr) {
    const nodes = [];
    
    // 3. Get owned items array
    const itemArrayPtr = await this.getOwnedItems(graphPtr);
    const arrayLength = await this.getArrayLength(itemArrayPtr);
    
    // 4. Iterate through items
    for (let i = 0; i < arrayLength; i++) {
        const itemPtr = await this.getArrayItem(itemArrayPtr, i);
        const itemName = await this.getName(itemPtr);
        const itemType = await this.getType(itemPtr);
        const isGraph = await this.isGraph(itemPtr);
        
        const node = {
            id: itemPtr,
            name: itemName,
            type: itemType,
            children: []
        };
        
        // 5. Recursively handle graphs
        if (isGraph) {
            node.children = await this.syncSceneRecurse(itemPtr);
        }
        
        nodes.push(node);
    }
    
    return nodes;
}
```

**Key Details**:
- Use **synchronous** style with async/await (NOT Promise.all) to avoid overwhelming Octane
- Preserve exact API call sequence: `getOwnedItems` → `size` → `get` (per item) → `name`/`type`/`isGraph`
- Handle ObjectRef structures throughout (don't extract just the handle)

#### Camera Synchronization
The Python proxy has special handling for camera sync:
- `setCameraPosition()` and `setCameraTarget()` methods
- Mouse drag events in viewport must send live updates to Octane
- Preserve exact coordinate transformation logic

#### Callback Rendering System
**CRITICAL**: `CallbackRenderViewport.js` has specific buffer handling:
- Register for `OnNewImage` callbacks
- Handle HDR/LDR buffer conversion correctly
- Prevent garbage frames with proper buffer isolation (see `convertHDRRGBA`)
- Maintain consistent frame display

### 5. Development Plan (Step-by-Step)

#### Phase 1: Project Setup
1. Create React app with Vite + TypeScript
2. Set up Node.js Express backend with gRPC
3. Load proto files and create gRPC service clients
4. Test basic connection to Octane (health check)

#### Phase 2: Core gRPC Client
1. Implement `makeApiCall()` equivalent with proper ObjectRef handling
2. Create helper methods for each service:
   - `ApiProjectManager`: rootNodeGraph()
   - `ApiNodeGraph`: getOwnedItems(), isValid()
   - `ApiItemArray`: size(), get()
   - `ApiItem`: name(), type()
   - `ApiNode`: destinationNodes()
3. Test scene loading with real Octane connection

#### Phase 3: UI Components (Scene Outliner First)
1. Analyze `SceneOutlinerSync.js` to find actual CSS classes used
2. Create React component with identical HTML structure
3. Port CSS styles (only used classes)
4. Implement tree expansion/collapse logic
5. Test with real scene data

#### Phase 4: Render Viewport
1. Port `CallbackRenderViewport.js` logic
2. Implement canvas rendering with proper HDR handling
3. Add mouse drag → camera sync integration
4. Test real-time rendering

#### Phase 5: Node Graph Editor & Inspector
1. Port `NodeGraphEditor.js` with context menus
2. Port `NodeInspector.js` with dynamic form generation
3. Preserve all parameter editing functionality
4. Test node creation and editing

#### Phase 6: Polish & Verification
1. Pixel-perfect CSS comparison with octaneWeb
2. Feature parity checklist (every button, every menu item)
3. Performance optimization (match or exceed octaneWeb)
4. Cross-browser testing

### 6. Testing Strategy

#### Unit Tests (Proto Loading)
```typescript
test('loads all required proto files', () => {
    expect(grpcClients).toHaveProperty('LiveLink');
    expect(grpcClients).toHaveProperty('ApiProjectManager');
    expect(grpcClients).toHaveProperty('ApiNodeGraph');
    expect(grpcClients).toHaveProperty('ApiItem');
    expect(grpcClients).toHaveProperty('ApiItemArray');
    expect(grpcClients).toHaveProperty('ApiNode');
});
```

#### Integration Tests (Real Octane)
```typescript
test('loads scene tree', async () => {
    const rootGraph = await octaneClient.getRootNodeGraph();
    expect(rootGraph).toHaveProperty('handle');
    expect(rootGraph).toHaveProperty('type');
    
    const items = await octaneClient.getOwnedItems(rootGraph);
    expect(items).toHaveProperty('handle');
});
```

#### Visual Regression Tests
- Screenshot comparison: octaneWeb vs octaneWebR
- CSS class usage audit (ensure no missing styles)
- Layout measurements (panel sizes, spacing)

### 7. Common Pitfalls to Avoid

#### ❌ DON'T: Extract handles as strings
```typescript
// ❌ WRONG
const rootGraph = await getRootNodeGraph();
const handle = rootGraph.handle;  // Extracting string
await getOwnedItems(handle);      // Loses type information
```

#### ✅ DO: Keep ObjectRef intact
```typescript
// ✅ CORRECT
const rootGraph = await getRootNodeGraph();
await getOwnedItems(rootGraph);  // Pass full ObjectRef
```

#### ❌ DON'T: Use all CSS classes blindly
```typescript
// ❌ WRONG - importing unused CSS
import 'octaneWeb/css/octane-theme.css';  // 2000+ lines, 60% unused
```

#### ✅ DO: Extract only used CSS
```typescript
// ✅ CORRECT - analyze component DOM construction
// NodeInspector.js uses: .node-inspector, .param-row, .param-label, .param-value
// Only port those classes
```

#### ❌ DON'T: Change API call order
```typescript
// ❌ WRONG - parallel calls can overwhelm Octane
const [name, type, isGraph] = await Promise.all([
    getName(item),
    getType(item),
    isGraph(item)
]);
```

#### ✅ DO: Preserve sequential calls
```typescript
// ✅ CORRECT - sequential as in octaneWeb
const name = await getName(item);
const type = await getType(item);
const isGraphBool = await isGraph(item);
```

### 8. Success Criteria

Your octaneWebR is complete when:

1. **Visual**: Side-by-side screenshots of octaneWeb and octaneWebR are indistinguishable
2. **Functional**: All features work identically (scene loading, node editing, camera sync, rendering)
3. **Technical**: Direct Node.js gRPC (no Python proxy), all proto files loaded correctly
4. **Performance**: Matches or exceeds octaneWeb responsiveness
5. **Code Quality**: Clean TypeScript with proper types, modular React components

### 9. Reference Materials

Study these files in depth:

**Core Logic**:
- `octaneWeb/js/core/OctaneWebClient.js` - All gRPC calls, syncScene algorithm
- `octaneProxy/octane_proxy.py` - How Python proxy handles requests (replicate this)
- `octaneProxy/grpc_registry.py` - Service/method/request type mappings

**UI Construction**:
- `octaneWeb/js/components/SceneOutlinerSync.js::buildTreeElement()` - Actual CSS classes used
- `octaneWeb/js/components/NodeInspector.js::renderParameter()` - Form generation logic
- `octaneWeb/js/components/GenericNodeRenderer.js` - Node rendering patterns

**Proto Definitions**:
- `sdk/src/api/grpc/protodef/common.proto` - ObjectRef definition
- `sdk/src/api/grpc/protodef/apinodesystem_6.proto` - getOwnedItemsRequest structure
- `sdk/src/api/grpc/protodef/livelink.proto` - Camera sync methods

### 10. Communication Protocol

**When you need guidance**, provide:
1. Specific file/function you're working on
2. Error message (if any) with full stack trace
3. What you expected vs what you got
4. Relevant code snippet (10-20 lines of context)

**When you complete a phase**, report:
1. What works (with evidence - screenshots, test results)
2. What doesn't work (with specific details)
3. Any deviations from octaneWeb (and justification)

---

## 🎓 Final Notes

This is a **port, not a rewrite**. Your goal is to:
1. **Preserve** all logic, especially the syncScene algorithm
2. **Translate** vanilla JS → React, Python → Node.js
3. **Match** the UI pixel-for-pixel using only the CSS actually used
4. **Validate** against real Octane (not mocks/stubs)

The octaneWeb codebase is your **specification**. When in doubt, match octaneWeb's behavior exactly. The Python proxy hides complexity that you must replicate in Node.js - study `octane_proxy.py` carefully to understand how it dynamically handles different request types.

Good luck! You have a complete working reference implementation. Use it well. 🚀
