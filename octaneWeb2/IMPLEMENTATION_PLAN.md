# OctaneWeb2 Implementation Plan

## Current Status: Phase 1 Complete ✅

The React foundation is in place with:
- ✅ Project structure created
- ✅ TypeScript configured
- ✅ Core layout components (MenuBar, StatusBar, MainLayout)
- ✅ Basic RenderViewport component
- ✅ Zustand stores (connection, render)
- ✅ OctaneClient API singleton
- ✅ Development server running on port 42219

## Phase 2: Core Rendering & Callbacks (NEXT)

### 2.1 WebSocket Callback Stream
Create hook for receiving render updates from Python proxy:

**File**: `src/hooks/useRenderCallback.ts`
```typescript
export const useRenderCallback = () => {
  const setImageData = useRenderStore(state => state.setImageData);
  
  useEffect(() => {
    const ws = new WebSocket('ws://localhost:51023/stream');
    
    ws.onmessage = (event) => {
      // Parse HDR/LDR buffer from proxy
      const imageData = parseRenderBuffer(event.data);
      setImageData(imageData);
    };
    
    return () => ws.close();
  }, []);
};
```

**Usage**: Call in `MainLayout` to start receiving frames

### 2.2 FPS Counter
Update `useRenderStore` to track frame timing:

```typescript
// In renderStore.ts
let lastFrameTime = Date.now();
let frameCount = 0;

const updateFPS = () => {
  const now = Date.now();
  frameCount++;
  
  if (now - lastFrameTime >= 1000) {
    set({ fps: frameCount });
    frameCount = 0;
    lastFrameTime = now;
  }
};
```

### 2.3 HDR/LDR Buffer Processing
Port buffer conversion logic from original:

**File**: `src/utils/bufferProcessing.ts`
```typescript
export const convertHDRtoImageData = (buffer: ArrayBuffer): ImageData => {
  // Port convertHDRRGBA from original CallbackRenderViewport.js
};

export const convertLDRtoImageData = (buffer: ArrayBuffer): ImageData => {
  // Port buffer processing from original
};
```

**Estimated Time**: 1-2 days

---

## Phase 3: Camera Controls

### 3.1 Mouse Camera Controls Hook
Centralized camera interaction:

**File**: `src/hooks/useCameraControls.ts`
```typescript
export const useCameraControls = (canvasRef: RefObject<HTMLCanvasElement>) => {
  const [isDragging, setIsDragging] = useState(false);
  const [lastPos, setLastPos] = useState({ x: 0, y: 0 });
  
  const handleMouseDown = (e: MouseEvent) => {
    setIsDragging(true);
    setLastPos({ x: e.clientX, y: e.clientY });
  };
  
  const handleMouseMove = async (e: MouseEvent) => {
    if (!isDragging) return;
    
    const deltaX = e.clientX - lastPos.x;
    const deltaY = e.clientY - lastPos.y;
    
    // Calculate new camera position/target
    const newPosition = calculateCameraPosition(deltaX, deltaY);
    
    // Send to Octane
    await octaneClient.setCameraPosition(newPosition);
    
    setLastPos({ x: e.clientX, y: e.clientY });
  };
  
  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    
    canvas.addEventListener('mousedown', handleMouseDown);
    window.addEventListener('mousemove', handleMouseMove);
    window.addEventListener('mouseup', () => setIsDragging(false));
    
    return () => {
      // cleanup
    };
  }, [isDragging, lastPos]);
};
```

### 3.2 Camera Math Utilities
**File**: `src/utils/cameraUtils.ts`
- `calculateCameraPosition(deltaX, deltaY): Vector3`
- `calculateCameraTarget(deltaX, deltaY): Vector3`
- `arcballRotation(x, y): Matrix4`

**Estimated Time**: 1 day

---

## Phase 4: Scene Outliner

### 4.1 Scene Store
**File**: `src/store/sceneStore.ts`
```typescript
interface SceneState {
  nodes: SceneNode[];
  selectedNodeId: string | null;
  expandedNodeIds: Set<string>;
  
  setNodes: (nodes: SceneNode[]) => void;
  selectNode: (id: string) => void;
  toggleExpanded: (id: string) => void;
  toggleVisibility: (id: string) => void;
}
```

### 4.2 Scene Tree Component
**File**: `src/components/sceneOutliner/SceneTree.tsx`

Recursive tree component with:
- Expand/collapse triangles
- Node icons (mesh, light, camera, etc.)
- Visibility toggles (eye icon)
- Click to select
- Keyboard navigation (arrow keys)

### 4.3 Scene Sync Hook
**File**: `src/hooks/useSceneSync.ts`
```typescript
export const useSceneSync = () => {
  const setNodes = useSceneStore(state => state.setNodes);
  
  useQuery({
    queryKey: ['sceneTree'],
    queryFn: () => octaneClient.getSceneTree(),
    onSuccess: (data) => setNodes(data),
    refetchInterval: 5000, // Poll every 5s
  });
};
```

**Estimated Time**: 2 days

---

## Phase 5: Node Inspector

### 5.1 Parameter Renderer Components
**File**: `src/components/nodeInspector/parameterRenderers/`

Create specialized input components:
- `NumberInput.tsx` - Sliders and numeric inputs
- `ColorPicker.tsx` - Color selection
- `BooleanToggle.tsx` - Checkboxes
- `EnumSelect.tsx` - Dropdown menus
- `TextInput.tsx` - String inputs

### 5.2 Node Inspector Component
**File**: `src/components/nodeInspector/NodeInspector.tsx`

Display parameters for selected node:
```typescript
export const NodeInspector = () => {
  const selectedNodeId = useSceneStore(state => state.selectedNodeId);
  
  const { data: parameters } = useQuery({
    queryKey: ['nodeParameters', selectedNodeId],
    queryFn: () => octaneClient.getNodeParameters(selectedNodeId!),
    enabled: !!selectedNodeId,
  });
  
  if (!selectedNodeId) {
    return <div className="empty-message">No node selected</div>;
  }
  
  return (
    <div className="node-inspector">
      {parameters?.map(param => (
        <ParameterRenderer key={param.name} parameter={param} />
      ))}
    </div>
  );
};
```

### 5.3 Parameter Update Hook
**File**: `src/hooks/useParameterUpdate.ts`
```typescript
export const useParameterUpdate = () => {
  const queryClient = useQueryClient();
  
  return useMutation({
    mutationFn: ({ nodeId, paramName, value }) => 
      octaneClient.setNodeParameter(nodeId, paramName, value),
    onSuccess: (_, { nodeId }) => {
      // Invalidate cache to refetch parameters
      queryClient.invalidateQueries(['nodeParameters', nodeId]);
    },
  });
};
```

**Estimated Time**: 2-3 days

---

## Phase 6: Node Graph Editor

### 6.1 Node Graph Store
**File**: `src/store/nodeGraphStore.ts`
```typescript
interface NodeGraphState {
  nodes: GraphNode[];
  connections: Connection[];
  selectedNodes: Set<string>;
  draggedNode: string | null;
  panOffset: { x: number; y: number };
  zoom: number;
  
  addNode: (type: string, position: { x: number; y: number }) => void;
  deleteNode: (id: string) => void;
  connectPorts: (from: PortRef, to: PortRef) => void;
  disconnectPort: (portId: string) => void;
}
```

### 6.2 Node Graph Canvas Component
**File**: `src/components/nodeGraph/NodeGraphCanvas.tsx`

Canvas-based node editor with:
- SVG rendering for nodes and connections
- Drag to pan canvas
- Mouse wheel zoom
- Click to select nodes
- Drag nodes to reposition

### 6.3 Context Menu Component
**File**: `src/components/nodeGraph/ContextMenu.tsx`

Right-click menu for:
- "Add Node" → submenu with node types
- "Delete Node"
- "Duplicate Node"
- "Copy/Paste"

### 6.4 Node Type Registry
**File**: `src/utils/nodeTypeRegistry.ts`

Define all available Octane node types:
```typescript
export const NODE_TYPES = {
  materials: ['Diffuse', 'Glossy', 'Specular', ...],
  lights: ['Daylight', 'HDRI', 'PointLight', ...],
  textures: ['ImageTexture', 'Noise', 'Gradient', ...],
  // ... etc
};
```

**Estimated Time**: 3-4 days

---

## Phase 7: Keyboard Shortcuts

### 7.1 Centralized Shortcut Hook
**File**: `src/hooks/useKeyboardShortcuts.ts`

ALL keyboard shortcuts in one place:
```typescript
export const useKeyboardShortcuts = () => {
  useEffect(() => {
    const handleKeyDown = (e: KeyboardEvent) => {
      // Ctrl+S - Save
      if (e.ctrlKey && e.key === 's') {
        e.preventDefault();
        handleSave();
      }
      
      // Ctrl+O - Open
      if (e.ctrlKey && e.key === 'o') {
        e.preventDefault();
        handleOpen();
      }
      
      // Space - Start/Stop Render
      if (e.key === ' ' && !isInputFocused()) {
        e.preventDefault();
        toggleRender();
      }
      
      // Ctrl+D - Toggle Debug Console
      if (e.ctrlKey && e.key === 'd') {
        e.preventDefault();
        toggleDebugConsole();
      }
      
      // F11 - Toggle Fullscreen
      if (e.key === 'F11') {
        e.preventDefault();
        toggleFullscreen();
      }
      
      // Delete - Delete selected nodes
      if (e.key === 'Delete' || e.key === 'Backspace') {
        if (!isInputFocused()) {
          e.preventDefault();
          deleteSelectedNodes();
        }
      }
      
      // Arrow keys - Navigate scene tree
      if (['ArrowUp', 'ArrowDown', 'ArrowLeft', 'ArrowRight'].includes(e.key)) {
        if (isFocusedOnSceneTree()) {
          e.preventDefault();
          navigateSceneTree(e.key);
        }
      }
    };
    
    window.addEventListener('keydown', handleKeyDown);
    return () => window.removeEventListener('keydown', handleKeyDown);
  }, []);
};
```

**Usage**: Call once in `App.tsx`

**Estimated Time**: 0.5 day

---

## Phase 8: Debug Console

### 8.1 Console Store
**File**: `src/store/consoleStore.ts`
```typescript
interface ConsoleState {
  isVisible: boolean;
  logs: LogEntry[];
  
  toggle: () => void;
  addLog: (message: string, level: 'info' | 'warn' | 'error') => void;
  clear: () => void;
}
```

### 8.2 Debug Console Component
**File**: `src/components/debug/DebugConsole.tsx`

Overlay console with:
- Log messages with timestamps
- Color-coded by level (info/warn/error)
- Auto-scroll to bottom
- Filter by level
- Clear button

### 8.3 Console Interceptor
Intercept `console.log/warn/error` and route to debug console:

**File**: `src/utils/consoleInterceptor.ts`
```typescript
export const setupConsoleInterceptor = () => {
  const originalLog = console.log;
  console.log = (...args) => {
    useConsoleStore.getState().addLog(args.join(' '), 'info');
    originalLog(...args);
  };
  
  // Same for console.warn and console.error
};
```

**Estimated Time**: 1 day

---

## Phase 9: Menu Bar Actions

### 9.1 File Menu Actions
- Open Scene (.orbx)
- Save Scene
- Export Image
- Recent Files

### 9.2 Edit Menu Actions
- Undo/Redo (if applicable)
- Copy/Paste nodes

### 9.3 Script Menu
- Run Python script
- Script editor (if needed)

### 9.4 Module Menu
- Load/unload Octane modules

### 9.5 Cloud Menu
- OctaneRender Cloud integration

### 9.6 Window Menu
- Toggle panels visibility
- Reset layout

### 9.7 Help Menu
- Documentation
- About

**Implementation**: Create a store and hook for each menu

**Estimated Time**: 2 days

---

## Phase 10: Polish & Optimization

### 10.1 Loading States
Add loading spinners and skeleton screens:
- Scene tree loading
- Node parameters loading
- Render starting

### 10.2 Error Boundaries
Wrap components in error boundaries to prevent full app crashes:

**File**: `src/components/common/ErrorBoundary.tsx`

### 10.3 Responsive Design
Ensure layout works on smaller screens:
- Collapsible side panels
- Mobile-friendly touch controls

### 10.4 Accessibility
- Keyboard navigation
- ARIA labels
- Focus management

### 10.5 Performance Profiling
- Use React DevTools Profiler
- Optimize re-renders with `React.memo`
- Add `useCallback` where needed

**Estimated Time**: 2-3 days

---

## Phase 11: Testing & Documentation

### 11.1 Unit Tests
Create tests for:
- Zustand stores
- Utils (camera math, buffer processing)
- Custom hooks

**Tool**: Vitest (already compatible with Vite)

### 11.2 Integration Tests
Test full user flows:
- Connect to Octane → Load scene → Render
- Select node → Edit parameters → See changes

**Tool**: Playwright or Cypress

### 11.3 Documentation
- Component API docs (JSDoc comments)
- Architecture diagrams
- Contributing guide

**Estimated Time**: 3 days

---

## Total Timeline Estimate

| Phase | Duration | Status |
|-------|----------|--------|
| 1. Project Setup | 0.5 day | ✅ Complete |
| 2. Core Rendering | 1-2 days | ⏳ Next |
| 3. Camera Controls | 1 day | 🔜 |
| 4. Scene Outliner | 2 days | 🔜 |
| 5. Node Inspector | 2-3 days | 🔜 |
| 6. Node Graph | 3-4 days | 🔜 |
| 7. Keyboard Shortcuts | 0.5 day | 🔜 |
| 8. Debug Console | 1 day | 🔜 |
| 9. Menu Actions | 2 days | 🔜 |
| 10. Polish | 2-3 days | 🔜 |
| 11. Testing | 3 days | 🔜 |

**Total**: 18-22 days

**Realistic with breaks**: 3-4 weeks

---

## Migration Strategy

### Parallel Development
Keep original octaneWeb running while building React version. Once feature parity is reached, switch over.

### Port Priority
1. ✅ Layout and styling
2. 🔥 Core rendering (most important)
3. 🔥 Camera controls (most used)
4. Scene outliner
5. Node inspector
6. Node graph
7. Debug tools
8. Menu actions

### Code Reuse
- Copy CSS variables from original `octane-theme.css`
- Port buffer processing logic from `CallbackRenderViewport.js`
- Reference keyboard shortcuts from original `app.js`
- Reuse Octane API endpoints (already defined in proxy)

---

## Success Criteria

The React rebuild is complete when:

1. ✅ All UI components match original UX
2. ✅ Keyboard shortcuts work (centralized, no duplicates)
3. ✅ Real-time rendering displays correctly
4. ✅ Camera controls sync with Octane
5. ✅ Scene outliner shows full hierarchy
6. ✅ Node inspector edits parameters
7. ✅ Node graph creates/connects nodes
8. ✅ Code is <7,000 lines TypeScript (50% reduction)
9. ✅ TypeScript compiles with no errors
10. ✅ App runs smoothly at 60 FPS

---

## Next Steps (Immediate)

1. **Port buffer processing** from original `CallbackRenderViewport.js`:
   - `convertHDRRGBA()`
   - `convertLDRRGBA()`
   
2. **Create WebSocket hook** to receive render callbacks

3. **Test rendering** with Octane running

Once rendering works, the foundation is solid for building out the rest.
