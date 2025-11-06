# OctaneWeb2 Component Relationship Map

## Component Dependency Graph

This document shows how components interact with stores, hooks, and each other.

```
┌─────────────────────────────────────────────────────────────────────┐
│                            App.tsx                                   │
│  - React Query Provider                                              │
│  - Global keyboard shortcuts hook                                    │
│  - Performance monitoring hook                                       │
└─────────────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────────────┐
│                         MainLayout                                   │
│  - Overall application layout (CSS Grid)                             │
│  - Connects MenuBar, Panels, StatusBar                              │
└─────────────────────────────────────────────────────────────────────┘
       │         │           │            │              │
       ▼         ▼           ▼            ▼              ▼
   ┌─────┐  ┌─────┐    ┌─────────┐  ┌─────────┐  ┌──────────┐
   │Menu │  │Scene│    │ Render  │  │  Node   │  │  Status  │
   │Bar  │  │Out  │    │Viewport │  │Inspector│  │   Bar    │
   └─────┘  │liner│    └─────────┘  └─────────┘  └──────────┘
            └─────┘
```

## Component-Store-Hook Matrix

| Component | Stores Used | Hooks Used | API Calls |
|-----------|------------|------------|-----------|
| **App** | - | useKeyboardShortcuts, usePerformanceMonitor | - |
| **MainLayout** | uiStore | - | - |
| **MenuBar** | connectionStore | useOctaneConnection | ping |
| **StatusBar** | connectionStore, renderStore | - | - |
| **SceneOutliner** | sceneStore, selectionStore | useSceneTree, useNodeSelection | getSceneTree |
| **RenderViewport** | renderStore | useCallbackStream, useCamera | setCameraPosition, setCameraTarget |
| **NodeInspector** | selectionStore | useNodeParameters | getNodeParameters, setNodeParameter |
| **NodeGraphEditor** | nodeGraphStore, selectionStore | useNodeGraph | createNode, deleteNode, connectNodes |

## Detailed Component Breakdown

### 1. App.tsx (Root)

```
App.tsx
├── Provides: QueryClientProvider (React Query context)
├── Uses Hooks:
│   ├── useKeyboardShortcuts() - Global keyboard handling
│   └── usePerformanceMonitor() - FPS tracking
└── Renders: <MainLayout />
```

**Responsibilities**:
- Setup React Query
- Setup global hooks (keyboard, performance)
- Render root layout

**No Direct Dependencies**: Top-level component

---

### 2. MainLayout (Layout Orchestrator)

```
MainLayout.tsx
├── Uses Stores:
│   └── uiStore (panel visibility, sizes)
├── Renders:
│   ├── <MenuBar /> (top)
│   ├── <PanelLayout>
│   │   ├── <SceneOutliner /> (left)
│   │   ├── <RenderViewport /> (center)
│   │   ├── <NodeInspector /> (right)
│   │   └── <NodeGraphEditor /> (bottom - conditional)
│   └── <StatusBar /> (bottom)
└── Handles: Layout resizing, panel visibility
```

**Responsibilities**:
- Layout management (CSS Grid)
- Panel resize handles
- Conditional panel rendering

**Dependencies**:
- uiStore (for panel state)

---

### 3. MenuBar (Top Navigation)

```
MenuBar.tsx
├── Uses Stores:
│   └── connectionStore (connection state)
├── Uses Hooks:
│   └── useOctaneConnection() (connect/disconnect)
├── API Calls:
│   └── octaneClient.ping()
├── Renders:
│   ├── Menu items (File, Edit, Script, etc.)
│   ├── <ConnectionStatus />
│   └── <Toggle /> (connection switch)
└── Handles: Menu dropdowns, connection toggle
```

**Responsibilities**:
- Top menu navigation
- Connection management UI
- Connection status display

**Dependencies**:
- connectionStore
- useOctaneConnection hook
- octaneClient API

**Child Components**:
- ConnectionStatus
- MenuItem (common component)

---

### 4. SceneOutliner (Left Panel)

```
SceneOutliner.tsx
├── Uses Stores:
│   ├── sceneStore (tree data, expand state)
│   └── selectionStore (selected nodes)
├── Uses Hooks:
│   ├── useSceneTree() (fetch tree from Octane)
│   └── useNodeSelection() (selection management)
├── API Calls:
│   ├── getSceneTree()
│   └── setNodeVisibility()
├── Renders:
│   ├── <OutlinerControls />
│   ├── <OutlinerTabs />
│   └── <SceneTree>
│       └── <SceneTreeNode> (recursive)
│           ├── <NodeIcon />
│           ├── <NodeLabel />
│           └── <VisibilityToggle />
└── Handles: Tree display, node selection, visibility toggles
```

**Responsibilities**:
- Display hierarchical scene tree
- Handle node selection (single/multi)
- Toggle node visibility
- Expand/collapse tree nodes
- Tab switching (Scene/LiveDB/LocalDB)

**Dependencies**:
- sceneStore (tree data)
- selectionStore (selection state)
- useSceneTree hook (data fetching)
- useNodeSelection hook (selection logic)

**Child Components**:
- OutlinerControls (expand/collapse all buttons)
- OutlinerTabs (Scene/LiveDB/LocalDB)
- SceneTree (recursive tree renderer)
- SceneTreeNode (individual tree nodes)

**State Flow**:
```
User clicks node → SceneTreeNode onClick
                 → selectionStore.selectNode(id)
                 → NodeInspector listens to selectionStore
                 → NodeInspector loads parameters for selected node
```

---

### 5. RenderViewport (Center Panel)

```
RenderViewport.tsx
├── Uses Stores:
│   └── renderStore (image data, render stats)
├── Uses Hooks:
│   ├── useCallbackStream() (real-time image updates)
│   ├── useCamera() (camera sync)
│   └── useDragGesture() (mouse drag handling)
├── API Calls:
│   ├── setCameraPosition()
│   └── setCameraTarget()
├── Renders:
│   ├── <ViewportHeader>
│   │   └── <ViewportControls />
│   ├── <canvas> (main render display)
│   ├── <ViewportOverlay>
│   │   └── <RenderStats />
│   └── <RenderToolbar />
└── Handles: Image display, mouse drag camera, render controls
```

**Responsibilities**:
- Display real-time render output
- Handle mouse drag for camera control
- Show render statistics (samples, time, FPS)
- Viewport controls (zoom, fit, etc.)
- Render toolbar (play, stop, reset)

**Dependencies**:
- renderStore (image data, stats)
- useCallbackStream (real-time updates)
- useCamera (camera sync)
- octaneClient API (camera updates)

**Child Components**:
- ViewportHeader
- ViewportControls (zoom, fit buttons)
- ViewportOverlay (stats display)
- RenderStats
- RenderToolbar (play, stop, etc.)

**Data Flow**:
```
Octane renders frame → callback_streamer.py (SSE)
                    → useCallbackStream hook
                    → renderStore.setImageData()
                    → RenderViewport re-renders
                    → Canvas draws new image

User drags mouse → useDragGesture
                → useCamera.updateCamera()
                → octaneClient.setCameraPosition()
                → Octane updates camera
                → New frame rendered (loop back to top)
```

---

### 6. NodeInspector (Right Panel)

```
NodeInspector.tsx
├── Uses Stores:
│   └── selectionStore (currently selected node)
├── Uses Hooks:
│   └── useNodeParameters(nodeId) (fetch parameters)
├── API Calls:
│   ├── getNodeParameters(nodeId)
│   └── setNodeParameter(nodeId, name, value)
├── Renders:
│   ├── <QuickAccessButtons />
│   └── <ParameterGroups>
│       └── <ParameterGroup> (collapsible sections)
│           └── <ParameterControl> (for each parameter)
│               ├── <NumberInput /> (sliders, numeric inputs)
│               ├── <ColorPicker /> (color parameters)
│               ├── <Checkbox /> (boolean parameters)
│               ├── <TextInput /> (string parameters)
│               └── <Dropdown /> (enum parameters)
└── Handles: Display/edit node parameters, live updates to Octane
```

**Responsibilities**:
- Display parameters for selected node
- Provide appropriate UI for each parameter type
- Send parameter changes to Octane in real-time
- Quick access buttons (camera, render target, etc.)
- Collapsible parameter groups

**Dependencies**:
- selectionStore (which node is selected)
- useNodeParameters hook (parameter data)
- octaneClient API (parameter updates)

**Child Components**:
- QuickAccessButtons
- ParameterGroups
- ParameterGroup (collapsible)
- ParameterControl (abstract)
  - NumberInput
  - ColorPicker
  - Checkbox
  - TextInput
  - Dropdown

**State Flow**:
```
SceneOutliner: User selects node
             → selectionStore.selectNode(id)
             → NodeInspector listens to selectionStore
             → useNodeParameters(selectedId) fetches data
             → Parameters displayed in UI

User edits parameter
             → ParameterControl onChange
             → octaneClient.setNodeParameter(id, name, value)
             → Octane updates parameter
             → May trigger new render
```

---

### 7. NodeGraphEditor (Bottom Panel)

```
NodeGraphEditor.tsx
├── Uses Stores:
│   ├── nodeGraphStore (nodes, connections, view transform)
│   └── selectionStore (selected nodes in graph)
├── Uses Hooks:
│   └── useNodeGraph() (sync with Octane node graph)
├── API Calls:
│   ├── createNode(type)
│   ├── deleteNode(id)
│   └── connectNodes(from, to, fromPort, toPort)
├── Renders:
│   ├── <NodeGraphControls />
│   ├── <canvas> (node graph rendering)
│   ├── GraphNode (rendered on canvas)
│   ├── GraphConnection (rendered on canvas)
│   └── <ContextMenu /> (conditional, right-click)
│       └── <MenuItem /> (hierarchical node types)
└── Handles: Visual node graph, node creation, connections, pan/zoom
```

**Responsibilities**:
- Display visual node graph
- Handle node creation (right-click menu)
- Handle node connections (drag from port to port)
- Pan and zoom viewport
- Node selection
- Context menus

**Dependencies**:
- nodeGraphStore (graph state)
- selectionStore (selection state)
- useNodeGraph hook (sync with Octane)
- octaneClient API (graph operations)

**Child Components**:
- NodeGraphControls (add, delete, fit buttons)
- ContextMenu (hierarchical node creation)
- MenuItem (reusable)

**Rendering Strategy**:
- Canvas-based rendering for performance
- GraphNode and GraphConnection are not React components
- They're drawn directly on canvas using 2D context

**State Flow**:
```
User right-clicks → Show ContextMenu
                 → User selects node type
                 → octaneClient.createNode(type)
                 → nodeGraphStore.addNode(newNode)
                 → Canvas re-renders with new node

User drags from output port to input port
                 → Detect drag gesture
                 → Draw temporary connection line
                 → On drop: octaneClient.connectNodes(from, to, fromPort, toPort)
                 → nodeGraphStore.addConnection(connection)
                 → Canvas re-renders with connection
```

---

### 8. StatusBar (Bottom)

```
StatusBar.tsx
├── Uses Stores:
│   ├── connectionStore (connection status)
│   └── renderStore (FPS, render stats)
├── Uses Hooks:
│   └── usePerformanceMonitor() (FPS tracking)
├── Renders:
│   ├── Left section (status messages)
│   ├── Center section (info)
│   └── Right section (connection, FPS)
└── Handles: Display status information
```

**Responsibilities**:
- Show connection status
- Display FPS counter
- Show general status messages
- Display render progress

**Dependencies**:
- connectionStore
- renderStore
- usePerformanceMonitor hook

**No Child Components** (simple display only)

---

## Custom Hooks Details

### useKeyboardShortcuts()

```typescript
useKeyboardShortcuts()
├── Uses Stores:
│   ├── selectionStore (for delete, copy, paste)
│   ├── uiStore (for toggle debug)
│   └── nodeGraphStore (for node operations)
├── Registers: Single global keydown listener
├── Handles:
│   ├── Delete key → deleteSelected()
│   ├── Ctrl+D → toggleDebugMode()
│   ├── Ctrl+C → copyNodes()
│   ├── Ctrl+V → pasteNodes()
│   ├── F → frameSelected()
│   └── ... all other shortcuts
└── Cleanup: Removes listener on unmount
```

**Purpose**: Centralize ALL keyboard shortcuts in one place

**Used By**: App.tsx (global)

---

### useOctaneConnection()

```typescript
useOctaneConnection()
├── Uses Stores:
│   └── connectionStore
├── API Calls:
│   └── octaneClient.ping()
├── Provides:
│   ├── isConnected: boolean
│   ├── isConnecting: boolean
│   ├── connect: () => Promise<void>
│   └── disconnect: () => Promise<void>
└── Handles: Connection lifecycle, retries, error handling
```

**Purpose**: Manage connection to Octane LiveLink

**Used By**: MenuBar, MainLayout

---

### useSceneTree()

```typescript
useSceneTree()
├── Uses: React Query
├── API Calls:
│   └── octaneClient.getSceneTree()
├── Configuration:
│   ├── refetchInterval: 5000 (auto-refresh every 5s)
│   ├── retry: 3 (retry on failure)
│   └── staleTime: 2000 (cache for 2s)
├── Provides:
│   ├── data: SceneNode[] (tree structure)
│   ├── isLoading: boolean
│   ├── error: Error | null
│   └── refetch: () => Promise<void>
└── Updates: sceneStore when data changes
```

**Purpose**: Fetch and cache scene tree data

**Used By**: SceneOutliner

---

### useCallbackStream()

```typescript
useCallbackStream()
├── Uses Stores:
│   └── renderStore
├── Uses: EventSource (Server-Sent Events)
├── Connects to: http://localhost:51023/callback-stream
├── Receives: Real-time image data from Octane
├── Provides:
│   ├── imageData: ImageData | null
│   ├── isStreaming: boolean
│   └── error: Error | null
└── Updates: renderStore.setImageData() on each frame
```

**Purpose**: Real-time streaming of render output

**Used By**: RenderViewport

---

### useCamera()

```typescript
useCamera()
├── Uses Stores:
│   └── renderStore (current camera state)
├── API Calls:
│   ├── setCameraPosition(position)
│   └── setCameraTarget(target)
├── Provides:
│   ├── position: Vector3
│   ├── target: Vector3
│   ├── updateCamera: (dx, dy) => void
│   └── resetCamera: () => void
└── Handles: Camera calculations and sync with Octane
```

**Purpose**: Mouse drag camera control

**Used By**: RenderViewport

---

### useNodeParameters(nodeId)

```typescript
useNodeParameters(nodeId: string)
├── Uses: React Query
├── API Calls:
│   ├── octaneClient.getNodeParameters(nodeId)
│   └── octaneClient.setNodeParameter(nodeId, name, value)
├── Configuration:
│   ├── enabled: !!nodeId (only fetch if node selected)
│   └── staleTime: 10000 (parameters don't change often)
├── Provides:
│   ├── parameters: NodeParameter[]
│   ├── isLoading: boolean
│   ├── updateParameter: (name, value) => Promise<void>
│   └── refetch: () => Promise<void>
└── Auto-refetches when nodeId changes
```

**Purpose**: Fetch and update node parameters

**Used By**: NodeInspector

---

### useNodeGraph()

```typescript
useNodeGraph()
├── Uses Stores:
│   └── nodeGraphStore
├── API Calls:
│   ├── getNodeGraph()
│   ├── createNode(type)
│   ├── deleteNode(id)
│   └── connectNodes(from, to, fromPort, toPort)
├── Provides:
│   ├── nodes: Map<string, GraphNode>
│   ├── connections: Connection[]
│   ├── createNode: (type, position) => Promise<void>
│   ├── deleteNode: (id) => Promise<void>
│   └── connectNodes: (from, to, fromPort, toPort) => Promise<void>
└── Syncs: nodeGraphStore with Octane node graph
```

**Purpose**: Node graph operations and sync

**Used By**: NodeGraphEditor

---

### useNodeSelection()

```typescript
useNodeSelection()
├── Uses Stores:
│   └── selectionStore
├── Provides:
│   ├── selectedNodes: Set<string>
│   ├── selectNode: (id, multi?) => void
│   ├── clearSelection: () => void
│   └── deleteSelected: () => Promise<void>
└── Handles: Multi-select logic (Ctrl+click, Shift+click)
```

**Purpose**: Node selection management

**Used By**: SceneOutliner, NodeGraphEditor

---

### usePerformanceMonitor()

```typescript
usePerformanceMonitor()
├── Uses: requestAnimationFrame
├── Tracks:
│   ├── FPS (frames per second)
│   ├── Frame time (ms per frame)
│   └── Memory usage (if available)
├── Updates: Every frame
└── Provides: Real-time performance metrics
```

**Purpose**: FPS tracking and performance monitoring

**Used By**: App.tsx (global), StatusBar (display)

---

## Store Details

### connectionStore

```typescript
connectionStore
├── State:
│   ├── isConnected: boolean
│   ├── isConnecting: boolean
│   ├── serverUrl: string
│   └── error: string | null
├── Actions:
│   ├── setConnected(boolean)
│   ├── setConnecting(boolean)
│   ├── setError(string)
│   └── setServerUrl(string)
└── Subscribers: MenuBar, StatusBar, MainLayout
```

---

### sceneStore

```typescript
sceneStore
├── State:
│   ├── tree: SceneNode[]
│   ├── nodeMap: Map<string, SceneNode>
│   └── expandedNodes: Set<string>
├── Actions:
│   ├── setTree(tree)
│   ├── toggleExpand(id)
│   └── updateNode(id, updates)
└── Subscribers: SceneOutliner, SceneTreeNode
```

---

### selectionStore

```typescript
selectionStore
├── State:
│   ├── selectedNodes: Set<string>
│   └── hoveredNode: string | null
├── Actions:
│   ├── selectNode(id, multi?)
│   ├── clearSelection()
│   └── deleteSelected()
└── Subscribers: SceneOutliner, NodeInspector, NodeGraphEditor
```

---

### renderStore

```typescript
renderStore
├── State:
│   ├── imageData: ImageData | null
│   ├── isRendering: boolean
│   ├── samples: number
│   ├── renderTime: number
│   └── resolution: { width, height }
├── Actions:
│   ├── setImageData(data)
│   ├── updateStats(stats)
│   └── setRendering(boolean)
└── Subscribers: RenderViewport, StatusBar
```

---

### nodeGraphStore

```typescript
nodeGraphStore
├── State:
│   ├── nodes: Map<string, GraphNode>
│   ├── connections: Connection[]
│   ├── selectedNodes: Set<string>
│   └── viewTransform: { x, y, scale }
├── Actions:
│   ├── addNode(node)
│   ├── removeNode(id)
│   ├── addConnection(connection)
│   ├── removeConnection(id)
│   └── setViewTransform(transform)
└── Subscribers: NodeGraphEditor
```

---

### uiStore

```typescript
uiStore
├── State:
│   ├── debugMode: boolean
│   └── panels: {
│       sceneOutliner: { visible, width },
│       nodeInspector: { visible, width },
│       nodeGraph: { visible, height }
│     }
├── Actions:
│   ├── toggleDebugMode()
│   ├── togglePanel(name)
│   └── setPanelSize(name, size)
└── Subscribers: MainLayout, useKeyboardShortcuts
```

---

## Data Flow Examples

### Example 1: User Selects Node in Scene Outliner

```
1. User clicks node in SceneOutliner
   ↓
2. SceneTreeNode.onClick(nodeId)
   ↓
3. selectionStore.selectNode(nodeId)
   ↓ (automatic reactivity)
4. NodeInspector re-renders (subscribed to selectionStore)
   ↓
5. useNodeParameters(nodeId) fetches parameters
   ↓
6. React Query calls octaneClient.getNodeParameters(nodeId)
   ↓
7. HTTP POST to Python proxy
   ↓
8. gRPC call to Octane LiveLink
   ↓
9. Parameters returned to NodeInspector
   ↓
10. ParameterControl components render with parameter data
```

### Example 2: User Drags Mouse on Viewport

```
1. User drags mouse on RenderViewport canvas
   ↓
2. useDragGesture detects drag (dx, dy)
   ↓
3. useCamera.updateCamera(dx, dy)
   ↓
4. Calculate new camera position and target
   ↓
5. octaneClient.setCameraPosition(newPosition)
   ↓
6. HTTP POST to Python proxy
   ↓
7. gRPC call to Octane LiveLink
   ↓
8. Octane updates camera
   ↓
9. Octane renders new frame
   ↓
10. callback_streamer.py receives OnNewImage callback
    ↓
11. SSE stream sends image data to browser
    ↓
12. useCallbackStream receives data
    ↓
13. renderStore.setImageData(data)
    ↓ (automatic reactivity)
14. RenderViewport re-renders
    ↓
15. Canvas draws new image
```

### Example 3: User Changes Parameter Value

```
1. User changes slider in NodeInspector
   ↓
2. NumberInput.onChange(newValue)
   ↓
3. updateParameter(paramName, newValue) from useNodeParameters
   ↓
4. octaneClient.setNodeParameter(nodeId, paramName, newValue)
   ↓
5. HTTP POST to Python proxy
   ↓
6. gRPC call to Octane LiveLink
   ↓
7. Octane updates parameter
   ↓
8. Octane may trigger new render
   ↓
9. If render triggered, follows "Example 2" flow from step 9
```

---

## Summary

This component map shows:

1. **Clear Component Hierarchy**: Each component has specific responsibilities
2. **Unidirectional Data Flow**: Data flows from stores → hooks → components
3. **No Duplicate Pathways**: Each operation has exactly ONE path
4. **Store Subscriptions**: Components only re-render when their subscribed data changes
5. **API Layer Separation**: All Octane communication goes through octaneClient
6. **React Query Caching**: Automatic caching and refetching of API data

The architecture ensures that:
- Adding/removing features is easy (just add/remove components)
- Debugging is straightforward (clear data flow)
- Performance is optimized (fine-grained reactivity)
- Code is maintainable (clear boundaries and responsibilities)
