# OctaneWeb2 Architecture Documentation

## System Architecture Overview

```
┌─────────────────────────────────────────────────────────────────────┐
│                         OctaneWeb2 (React)                          │
│                                                                     │
│  ┌───────────────────────────────────────────────────────────────┐ │
│  │                      App.tsx (Root)                           │ │
│  │                                                               │ │
│  │  ┌─────────────────┐  ┌──────────────────┐  ┌─────────────┐ │ │
│  │  │ React Query     │  │ Zustand Stores   │  │ Global      │ │ │
│  │  │ Provider        │  │                  │  │ Hooks       │ │ │
│  │  └─────────────────┘  └──────────────────┘  └─────────────┘ │ │
│  └───────────────────────────────────────────────────────────────┘ │
│                                                                     │
│  ┌───────────────────────────────────────────────────────────────┐ │
│  │                    MainLayout Component                       │ │
│  │                                                               │ │
│  │  ┌──────────────────────────────────────────────────────────┐│ │
│  │  │ MenuBar + ConnectionStatus                               ││ │
│  │  └──────────────────────────────────────────────────────────┘│ │
│  │                                                               │ │
│  │  ┌────────────┐  ┌──────────────┐  ┌────────────────────┐  │ │
│  │  │ Scene      │  │  Render      │  │  Node Inspector    │  │ │
│  │  │ Outliner   │  │  Viewport    │  │                    │  │ │
│  │  │            │  │              │  │                    │  │ │
│  │  │ (Left)     │  │  (Center)    │  │  (Right)           │  │ │
│  │  └────────────┘  └──────────────┘  └────────────────────┘  │ │
│  │                                                               │ │
│  │  ┌──────────────────────────────────────────────────────────┐│ │
│  │  │ Node Graph Editor (Bottom)                               ││ │
│  │  └──────────────────────────────────────────────────────────┘│ │
│  │                                                               │ │
│  │  ┌──────────────────────────────────────────────────────────┐│ │
│  │  │ StatusBar                                                ││ │
│  │  └──────────────────────────────────────────────────────────┘│ │
│  └───────────────────────────────────────────────────────────────┘ │
└─────────────────────────────────────────────────────────────────────┘
                              ↕ HTTP/JSON
┌─────────────────────────────────────────────────────────────────────┐
│                     Python Proxy (Port 51023)                       │
│  ┌─────────────────────────────────────────────────────────────┐   │
│  │  octane_proxy.py + callback_streamer.py                     │   │
│  └─────────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────────┘
                              ↕ gRPC
┌─────────────────────────────────────────────────────────────────────┐
│                  Octane LiveLink Service (Port 51022)               │
└─────────────────────────────────────────────────────────────────────┘
```

## Data Flow Architecture

### 1. Connection & Initialization Flow
```
User clicks Connect
    ↓
useOctaneConnection hook
    ↓
connectionStore.setConnecting(true)
    ↓
OctaneClient.connect()
    ↓
HTTP POST to Python Proxy
    ↓
gRPC call to Octane LiveLink
    ↓
Connection established
    ↓
connectionStore.setConnected(true)
    ↓
Trigger initial data fetch
    ↓
useSceneTree, useRenderState hooks activate
    ↓
UI components update reactively
```

### 2. Real-time Callback Flow (Render Updates)
```
Octane renders frame
    ↓
Octane LiveLink OnNewImage callback
    ↓
callback_streamer.py (Python)
    ↓
Server-Sent Events (SSE) stream
    ↓
useCallbackStream hook (EventSource)
    ↓
renderStore.setImageData(data)
    ↓
RenderViewport re-renders
    ↓
Canvas draws new image
```

### 3. User Interaction Flow (Camera Drag)
```
User drags mouse on viewport
    ↓
RenderViewport onMouseMove
    ↓
useCamera.updateCamera(position, target)
    ↓
OctaneClient.setCameraPosition()
    ↓
HTTP POST to Python Proxy
    ↓
gRPC call to Octane
    ↓
Octane updates camera
    ↓
Triggers new render (callback flow)
```

### 4. Scene Tree Sync Flow
```
Component mounts with useSceneTree()
    ↓
React Query fetches data
    ↓
OctaneClient.getSceneTree()
    ↓
HTTP POST to Python Proxy
    ↓
gRPC call to Octane
    ↓
Receives scene hierarchy
    ↓
sceneStore.setTree(data)
    ↓
SceneOutliner re-renders
    ↓
Recursive SceneTreeNode components
```

### 5. Node Selection Flow
```
User clicks node in Scene Outliner
    ↓
SceneTreeNode onClick
    ↓
selectionStore.selectNode(id)
    ↓
Multiple components listen:
  - NodeInspector (shows parameters)
  - NodeGraphEditor (highlights node)
  - RenderViewport (updates selection overlay)
```

### 6. Parameter Edit Flow
```
User changes slider in NodeInspector
    ↓
ParameterControl onChange
    ↓
OctaneClient.setNodeParameter(id, param, value)
    ↓
HTTP POST to Python Proxy
    ↓
gRPC call to Octane
    ↓
Octane updates parameter
    ↓
Triggers new render (callback flow)
```

## State Management Architecture

### Zustand Store Structure

```typescript
// Connection Store
interface ConnectionState {
  isConnected: boolean;
  isConnecting: boolean;
  serverUrl: string;
  error: string | null;
  
  // Actions
  setConnected: (connected: boolean) => void;
  setError: (error: string) => void;
  connect: () => Promise<void>;
  disconnect: () => Promise<void>;
}

// Scene Store
interface SceneState {
  tree: SceneNode[];
  nodeMap: Map<string, SceneNode>;
  expandedNodes: Set<string>;
  
  // Actions
  setTree: (tree: SceneNode[]) => void;
  toggleExpand: (id: string) => void;
  toggleVisibility: (id: string) => void;
  refreshTree: () => Promise<void>;
}

// Selection Store
interface SelectionState {
  selectedNodes: Set<string>;
  hoveredNode: string | null;
  
  // Actions
  selectNode: (id: string, multi?: boolean) => void;
  clearSelection: () => void;
  deleteSelected: () => Promise<void>;
}

// Render Store
interface RenderState {
  isRendering: boolean;
  imageData: ImageData | null;
  samples: number;
  renderTime: number;
  resolution: { width: number; height: number };
  
  // Actions
  setImageData: (data: ImageData) => void;
  updateStats: (stats: RenderStats) => void;
  startRender: () => Promise<void>;
  stopRender: () => Promise<void>;
}

// Node Graph Store
interface NodeGraphState {
  nodes: Map<string, GraphNode>;
  connections: Connection[];
  selectedNodes: Set<string>;
  viewTransform: { x: number; y: number; scale: number };
  
  // Actions
  addNode: (type: string, position: Point) => void;
  removeNode: (id: string) => void;
  connectNodes: (from: string, to: string) => void;
  setViewTransform: (transform: Transform) => void;
}

// UI Store
interface UIState {
  debugMode: boolean;
  panels: {
    sceneOutliner: { visible: boolean; width: number };
    nodeInspector: { visible: boolean; width: number };
    nodeGraph: { visible: boolean; height: number };
  };
  
  // Actions
  toggleDebugMode: () => void;
  togglePanel: (panel: string) => void;
  setPanelSize: (panel: string, size: number) => void;
}
```

## Component Hierarchy

```
App
├── LoadingScreen (conditional)
└── MainLayout
    ├── MenuBar
    │   ├── MenuItem (File, Edit, Script, etc.)
    │   └── ConnectionStatus
    │       └── Toggle
    │
    ├── PanelLayout (CSS Grid)
    │   ├── LeftPanel
    │   │   └── SceneOutliner
    │   │       ├── OutlinerControls
    │   │       │   └── Button (expand, collapse, refresh)
    │   │       ├── OutlinerTabs
    │   │       │   └── Tab (Scene, LiveDB, LocalDB)
    │   │       └── SceneTree
    │   │           └── SceneTreeNode (recursive)
    │   │               ├── NodeIcon
    │   │               ├── NodeLabel
    │   │               └── VisibilityToggle
    │   │
    │   ├── CenterPanel
    │   │   └── ViewportContainer
    │   │       ├── ViewportHeader
    │   │       │   └── ViewportControls
    │   │       │       └── Button (zoom, fit, etc.)
    │   │       ├── RenderViewport
    │   │       │   └── canvas (ref)
    │   │       ├── ViewportOverlay
    │   │       │   └── RenderStats
    │   │       └── RenderToolbar
    │   │           └── Button (play, stop, reset, etc.)
    │   │
    │   ├── RightPanel
    │   │   └── NodeInspector
    │   │       ├── QuickAccessButtons
    │   │       │   └── Button (camera, render target, etc.)
    │   │       └── ParameterGroups
    │   │           └── ParameterGroup
    │   │               ├── GroupHeader (collapsible)
    │   │               └── Parameters
    │   │                   └── ParameterControl
    │   │                       ├── NumberInput (slider + input)
    │   │                       ├── ColorPicker
    │   │                       ├── Checkbox
    │   │                       ├── TextInput
    │   │                       └── Dropdown
    │   │
    │   └── BottomPanel
    │       └── NodeGraphEditor
    │           ├── NodeGraphControls
    │           │   └── Button (add, delete, fit)
    │           ├── canvas (ref)
    │           ├── GraphNode (rendered on canvas)
    │           ├── GraphConnection (rendered on canvas)
    │           └── ContextMenu (conditional)
    │               └── MenuItem (hierarchical)
    │
    ├── StatusBar
    │   ├── StatusLeft
    │   ├── StatusCenter
    │   └── StatusRight (FPS, connection status)
    │
    └── DebugConsole (conditional, Ctrl-D)
        ├── ConsoleHeader
        ├── ConsoleLog
        │   └── LogEntry
        └── ConsoleInput
```

## Custom Hooks Dependencies

```typescript
// Core Hooks (no dependencies)
useOctaneConnection()
├── Uses: connectionStore
└── Provides: connect, disconnect, isConnected

usePerformanceMonitor()
├── Uses: requestAnimationFrame
└── Provides: fps, frameTime

// Data Hooks (depend on connection)
useSceneTree()
├── Uses: useOctaneConnection, React Query, sceneStore
└── Provides: tree, isLoading, error, refetch

useRenderState()
├── Uses: useOctaneConnection, renderStore
└── Provides: imageData, stats, startRender, stopRender

useNodeParameters(nodeId)
├── Uses: useOctaneConnection, React Query
└── Provides: parameters, updateParameter, isLoading

// Interaction Hooks
useCamera()
├── Uses: useOctaneConnection, renderStore
└── Provides: position, target, updateCamera, resetCamera

useNodeSelection()
├── Uses: selectionStore, sceneStore
└── Provides: selectedNodes, selectNode, clearSelection

useKeyboardShortcuts()
├── Uses: useNodeSelection, uiStore, useCamera
└── Provides: (side effects only, registers global listeners)

// Streaming Hook
useCallbackStream()
├── Uses: useOctaneConnection, renderStore, EventSource
└── Provides: imageData, isStreaming, error
```

## API Layer Structure

```typescript
// api/OctaneClient.ts
class OctaneClient {
  private baseUrl: string;
  private isConnected: boolean;
  
  // Connection
  async connect(): Promise<void>
  async disconnect(): Promise<void>
  async ping(): Promise<boolean>
  
  // Scene Management (api/endpoints/scene.ts)
  async getSceneTree(): Promise<SceneNode[]>
  async getNodeInfo(id: string): Promise<NodeInfo>
  async setNodeVisibility(id: string, visible: boolean): Promise<void>
  
  // Camera Control (api/endpoints/camera.ts)
  async getCameraPosition(): Promise<Vector3>
  async setCameraPosition(pos: Vector3): Promise<void>
  async getCameraTarget(): Promise<Vector3>
  async setCameraTarget(target: Vector3): Promise<void>
  
  // Render Control (api/endpoints/render.ts)
  async startRender(): Promise<void>
  async stopRender(): Promise<void>
  async getRenderProgress(): Promise<RenderProgress>
  
  // Node Graph (api/endpoints/nodes.ts)
  async getNodeParameters(id: string): Promise<Parameter[]>
  async setNodeParameter(id: string, name: string, value: any): Promise<void>
  async createNode(type: string): Promise<string>
  async deleteNode(id: string): Promise<void>
  async connectNodes(from: string, to: string, fromPort: string, toPort: string): Promise<void>
  
  // Internal
  private async request(endpoint: string, data?: any): Promise<any>
}

// api/callbackStreamer.ts
class CallbackStreamer {
  private eventSource: EventSource | null;
  private onImageCallback: (data: ImageData) => void;
  
  async start(): Promise<void>
  async stop(): Promise<void>
  setImageCallback(callback: (data: ImageData) => void): void
}
```

## CSS Architecture

### Theme Structure
```css
/* styles/variables.css */
:root {
  /* OTOY Brand Colors */
  --color-bg-primary: #1a1a1a;
  --color-bg-secondary: #252525;
  --color-bg-tertiary: #2f2f2f;
  --color-bg-hover: #333333;
  
  --color-text-primary: #e0e0e0;
  --color-text-secondary: #a0a0a0;
  --color-text-disabled: #666666;
  
  --color-accent: #00d4ff;
  --color-accent-hover: #00b8e6;
  
  --color-border: #3a3a3a;
  --color-divider: #2a2a2a;
  
  /* Status Colors */
  --color-success: #4caf50;
  --color-warning: #ff9800;
  --color-error: #f44336;
  
  /* Spacing */
  --spacing-xs: 4px;
  --spacing-sm: 8px;
  --spacing-md: 16px;
  --spacing-lg: 24px;
  --spacing-xl: 32px;
  
  /* Typography */
  --font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
  --font-size-sm: 12px;
  --font-size-md: 14px;
  --font-size-lg: 16px;
  
  /* Layout */
  --header-height: 40px;
  --status-bar-height: 24px;
  --panel-min-width: 200px;
  --panel-max-width: 600px;
}
```

### Component Styling Strategy
- Use CSS Modules for component-scoped styles
- Global theme variables for consistency
- BEM naming convention for clarity
- Mobile-first responsive design
- Dark theme by default (OTOY standard)

## Performance Optimizations

### 1. Component Memoization
```typescript
// Expensive render components
export const SceneTreeNode = React.memo(({ node }) => {
  // Only re-renders when node changes
}, (prev, next) => prev.node.id === next.node.id);
```

### 2. Virtual Scrolling
```typescript
// For large scene trees
import { FixedSizeList } from 'react-window';

const SceneTree = ({ nodes }) => {
  return (
    <FixedSizeList
      height={600}
      itemCount={nodes.length}
      itemSize={24}
    >
      {({ index, style }) => (
        <div style={style}>
          <SceneTreeNode node={nodes[index]} />
        </div>
      )}
    </FixedSizeList>
  );
};
```

### 3. Zustand Selectors (Prevent Over-rendering)
```typescript
// BAD: Re-renders on ANY store change
const { selectedNodes, tree, expandedNodes } = useSceneStore();

// GOOD: Only re-renders when selectedNodes changes
const selectedNodes = useSceneStore(state => state.selectedNodes);
```

### 4. React Query Caching
```typescript
// Automatic caching and background refetching
const { data } = useQuery({
  queryKey: ['sceneTree'],
  queryFn: getSceneTree,
  staleTime: 5000,      // Consider fresh for 5s
  cacheTime: 300000,    // Keep in cache for 5min
  refetchInterval: 5000 // Auto-refresh every 5s
});
```

### 5. Canvas Rendering Optimization
```typescript
const RenderViewport = () => {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const frameIdRef = useRef<number>();
  
  const drawFrame = useCallback((imageData: ImageData) => {
    // Cancel previous frame request
    if (frameIdRef.current) {
      cancelAnimationFrame(frameIdRef.current);
    }
    
    // Request next frame
    frameIdRef.current = requestAnimationFrame(() => {
      const ctx = canvasRef.current?.getContext('2d');
      if (ctx) {
        ctx.putImageData(imageData, 0, 0);
      }
    });
  }, []);
  
  return <canvas ref={canvasRef} />;
};
```

## Error Handling Strategy

### 1. Error Boundaries
```typescript
class ErrorBoundary extends React.Component {
  state = { hasError: false, error: null };
  
  static getDerivedStateFromError(error) {
    return { hasError: true, error };
  }
  
  render() {
    if (this.state.hasError) {
      return <ErrorFallback error={this.state.error} />;
    }
    return this.props.children;
  }
}

// Usage
<ErrorBoundary>
  <NodeGraphEditor />
</ErrorBoundary>
```

### 2. API Error Handling
```typescript
const useSceneTree = () => {
  return useQuery({
    queryKey: ['sceneTree'],
    queryFn: getSceneTree,
    retry: 3,
    retryDelay: 1000,
    onError: (error) => {
      console.error('Failed to fetch scene tree:', error);
      // Show user-friendly notification
    }
  });
};
```

### 3. Connection Error Recovery
```typescript
const useOctaneConnection = () => {
  const connect = async () => {
    try {
      await octaneClient.connect();
      connectionStore.setConnected(true);
    } catch (error) {
      connectionStore.setError(error.message);
      // Show reconnect UI
    }
  };
};
```

## Accessibility Considerations

1. **Keyboard Navigation**: All interactive elements accessible via keyboard
2. **ARIA Labels**: Screen reader support for all components
3. **Focus Management**: Proper focus trapping in modals
4. **Color Contrast**: WCAG AA compliance
5. **Semantic HTML**: Proper heading structure and landmarks

## Browser Compatibility

- **Chrome**: 90+ (primary target)
- **Firefox**: 88+
- **Safari**: 14+
- **Edge**: 90+

## Development Tools

1. **React DevTools**: Component inspection
2. **Zustand DevTools**: State debugging
3. **React Query DevTools**: API debugging
4. **Performance Profiler**: Render optimization
5. **ESLint**: Code quality
6. **Prettier**: Code formatting

---

This architecture provides a solid foundation for building a maintainable, performant, and scalable React application that matches the octaneWeb UX while eliminating code duplication and providing a much cleaner codebase.
