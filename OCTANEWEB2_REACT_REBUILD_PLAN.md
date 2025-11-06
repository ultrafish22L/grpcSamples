# OctaneWeb2 - React Rebuild Plan

## Executive Summary

Complete rebuild of the octaneWeb standalone application using React library. The goal is to match the existing UX with much cleaner, more maintainable code while keeping the working gRPC communication and Python proxy unchanged.

## Current State Analysis

### Existing octaneWeb (Vanilla JavaScript)
- **Code Volume**: ~12,600 lines of JavaScript, ~5,250 lines of CSS
- **Architecture**: Manual DOM manipulation, custom event system, complex initialization sequences
- **Issues Identified**:
  - Duplicate event handling pathways (keyboard shortcuts in multiple places)
  - Scattered state management across components
  - Manual DOM updates causing complexity
  - Complex component lifecycle management
  - Duplicate code for similar operations
  - Tightly coupled components

### Working Components to Preserve
- ✅ gRPC communication via Python proxy (port 51023)
- ✅ Real-time callback streaming system
- ✅ Python proxy server (octaneProxy/octane_proxy.py & callback_streamer.py)
- ✅ Protocol buffers and API definitions

## React Architecture Design

### Technology Stack
```
Frontend:
- React 18.x (latest stable)
- TypeScript (for type safety and better developer experience)
- Zustand (lightweight state management - simpler than Redux)
- React Query (for async state and gRPC call management)
- CSS Modules or Styled Components (scoped styling)
- Vite (fast build tool, better than CRA)

Development:
- ESLint + Prettier (code quality)
- React DevTools (debugging)
```

### Project Structure
```
octaneWeb2/
├── public/                          # Static assets
│   └── assets/
│       └── icons/                   # OTOY icons
├── src/
│   ├── main.tsx                     # Application entry point
│   ├── App.tsx                      # Root component
│   │
│   ├── api/                         # gRPC Communication Layer
│   │   ├── OctaneClient.ts          # Main gRPC client (wraps proxy calls)
│   │   ├── callbackStreamer.ts      # Real-time callback handler
│   │   ├── endpoints/               # Organized API calls
│   │   │   ├── scene.ts             # Scene management APIs
│   │   │   ├── camera.ts            # Camera control APIs
│   │   │   ├── render.ts            # Render control APIs
│   │   │   └── nodes.ts             # Node graph APIs
│   │   └── types.ts                 # TypeScript types from protobuf
│   │
│   ├── components/                  # React Components
│   │   ├── layout/                  # Layout Components
│   │   │   ├── MainLayout.tsx       # Overall app layout
│   │   │   ├── MenuBar.tsx          # Top menu bar
│   │   │   ├── StatusBar.tsx        # Bottom status bar
│   │   │   └── ConnectionStatus.tsx # Connection indicator
│   │   │
│   │   ├── viewport/                # Render Viewport
│   │   │   ├── RenderViewport.tsx   # Main viewport component
│   │   │   ├── ViewportControls.tsx # Zoom, fit controls
│   │   │   ├── RenderToolbar.tsx    # Render control buttons
│   │   │   └── ViewportOverlay.tsx  # Stats overlay
│   │   │
│   │   ├── sceneOutliner/           # Scene Outliner Panel
│   │   │   ├── SceneOutliner.tsx    # Main outliner component
│   │   │   ├── SceneTree.tsx        # Hierarchical tree
│   │   │   ├── SceneTreeNode.tsx    # Individual tree node
│   │   │   ├── OutlinerTabs.tsx     # Scene/LiveDB/LocalDB tabs
│   │   │   └── OutlinerControls.tsx # Expand/collapse buttons
│   │   │
│   │   ├── nodeInspector/           # Node Inspector Panel
│   │   │   ├── NodeInspector.tsx    # Main inspector component
│   │   │   ├── ParameterGroup.tsx   # Collapsible parameter groups
│   │   │   ├── ParameterControl.tsx # Individual parameter editor
│   │   │   └── QuickAccessButtons.tsx # Camera, render target, etc.
│   │   │
│   │   ├── nodeGraph/               # Node Graph Editor
│   │   │   ├── NodeGraphEditor.tsx  # Canvas-based graph
│   │   │   ├── GraphNode.tsx        # Visual node representation
│   │   │   ├── GraphConnection.tsx  # Node connections
│   │   │   ├── ContextMenu.tsx      # Right-click menu
│   │   │   └── NodePalette.tsx      # Node creation palette
│   │   │
│   │   ├── common/                  # Reusable Components
│   │   │   ├── Button.tsx           # Styled button
│   │   │   ├── Input.tsx            # Form inputs
│   │   │   ├── Toggle.tsx           # Toggle switch
│   │   │   ├── Panel.tsx            # Collapsible panel
│   │   │   ├── ContextMenu.tsx      # Generic context menu
│   │   │   ├── Modal.tsx            # Modal dialog
│   │   │   └── LoadingScreen.tsx    # Loading overlay
│   │   │
│   │   └── debug/                   # Debug Components
│   │       └── DebugConsole.tsx     # Ctrl-D debug console
│   │
│   ├── hooks/                       # Custom React Hooks
│   │   ├── useOctaneConnection.ts   # Connection management
│   │   ├── useSceneTree.ts          # Scene state hook
│   │   ├── useNodeSelection.ts      # Node selection state
│   │   ├── useCamera.ts             # Camera sync hook
│   │   ├── useKeyboardShortcuts.ts  # Centralized keyboard handling
│   │   ├── useCallbackStream.ts     # Real-time callbacks
│   │   └── usePerformanceMonitor.ts # FPS tracking
│   │
│   ├── store/                       # State Management (Zustand)
│   │   ├── connectionStore.ts       # Connection state
│   │   ├── sceneStore.ts            # Scene hierarchy state
│   │   ├── selectionStore.ts        # Selection state
│   │   ├── renderStore.ts           # Render state
│   │   ├── nodeGraphStore.ts        # Node graph state
│   │   └── uiStore.ts               # UI state (panels, debug mode)
│   │
│   ├── utils/                       # Utility Functions
│   │   ├── camera.ts                # Camera calculations
│   │   ├── geometry.ts              # Graph geometry utils
│   │   ├── colors.ts                # Color conversions
│   │   ├── octaneTypes.ts           # Octane type mappings
│   │   └── logger.ts                # Centralized logging
│   │
│   ├── styles/                      # Global Styles
│   │   ├── theme.ts                 # OTOY theme constants
│   │   ├── global.css               # Global CSS
│   │   └── variables.css            # CSS variables
│   │
│   └── types/                       # TypeScript Types
│       ├── octane.ts                # Octane-specific types
│       ├── scene.ts                 # Scene types
│       └── ui.ts                    # UI types
│
├── index.html                       # HTML entry point
├── vite.config.ts                   # Vite configuration
├── tsconfig.json                    # TypeScript configuration
├── package.json                     # Dependencies
└── README.md                        # Documentation
```

## Key Architecture Improvements

### 1. Single Source of Truth for Events
**Problem**: Current code has keyboard shortcuts handled in multiple places
```javascript
// OLD (octaneWeb): KeyboardShortcuts.js + inline handlers + component handlers
```

**Solution**: Centralized keyboard handling
```typescript
// NEW (octaneWeb2): Single hook for all shortcuts
const useKeyboardShortcuts = () => {
  useEffect(() => {
    const handleKeyDown = (e: KeyboardEvent) => {
      // Single switch statement for ALL keyboard shortcuts
      switch (true) {
        case e.key === 'Delete':
          handleDelete();
          break;
        case e.ctrlKey && e.key === 'd':
          toggleDebugConsole();
          break;
        // ... all other shortcuts in ONE place
      }
    };
    window.addEventListener('keydown', handleKeyDown);
    return () => window.removeEventListener('keydown', handleKeyDown);
  }, []);
};
```

### 2. Centralized State Management with Zustand
**Problem**: State scattered across components and custom StateManager
```javascript
// OLD: Manual state updates, custom events
this.stateManager.updateState({ selection: nodeId });
this.eventSystem.emit('selectionChanged', nodeId);
```

**Solution**: Simple, reactive state stores
```typescript
// NEW: Zustand store (simpler than Redux, more powerful than Context)
const useSelectionStore = create((set) => ({
  selectedNodes: new Set(),
  selectNode: (id) => set((state) => ({ 
    selectedNodes: new Set([...state.selectedNodes, id]) 
  })),
  clearSelection: () => set({ selectedNodes: new Set() })
}));

// Usage in component:
const { selectedNodes, selectNode } = useSelectionStore();
```

### 3. React Query for gRPC Calls
**Problem**: Manual async handling and caching
```javascript
// OLD: Manual fetch and state updates
async fetchSceneTree() {
  const data = await this.client.getSceneTree();
  this.updateSceneTree(data);
}
```

**Solution**: React Query handles caching, refetching, loading states
```typescript
// NEW: Automatic caching, loading, error states
const { data: sceneTree, isLoading, error } = useQuery({
  queryKey: ['sceneTree'],
  queryFn: () => octaneClient.getSceneTree(),
  refetchInterval: 5000 // Auto-refresh
});
```

### 4. Component Composition Instead of Inheritance
**Problem**: Complex component initialization and lifecycle
```javascript
// OLD: Manual DOM manipulation
class CallbackRenderViewport {
  constructor(containerId) {
    this.container = document.getElementById(containerId);
    this.canvas = document.createElement('canvas');
    // ... manual setup
  }
}
```

**Solution**: Declarative React components
```typescript
// NEW: Clean, declarative
const RenderViewport = () => {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const { imageData } = useCallbackStream();
  
  useEffect(() => {
    if (canvasRef.current && imageData) {
      drawImageToCanvas(canvasRef.current, imageData);
    }
  }, [imageData]);
  
  return <canvas ref={canvasRef} />;
};
```

### 5. Custom Hooks for Reusable Logic
**Problem**: Duplicate logic across components
```javascript
// OLD: Copy-pasted camera logic in multiple files
```

**Solution**: Reusable hooks
```typescript
// NEW: Single hook used everywhere
const useCamera = () => {
  const [position, setPosition] = useState([0, 0, 5]);
  const [target, setTarget] = useState([0, 0, 0]);
  
  const updateCamera = useCallback((newPos, newTarget) => {
    setPosition(newPos);
    setTarget(newTarget);
    octaneClient.setCameraPosition(newPos);
    octaneClient.setCameraTarget(newTarget);
  }, []);
  
  return { position, target, updateCamera };
};
```

## Component Mapping (Old → New)

| Old Component (Vanilla JS) | New Component (React) | Changes |
|---------------------------|----------------------|---------|
| app.js (main orchestrator) | App.tsx + custom hooks | Split into smaller pieces |
| OctaneWebClient.js | api/OctaneClient.ts | TypeScript, same functionality |
| EventSystem.js | Zustand stores | Built-in reactivity |
| StateManager.js | Zustand stores | Simpler state management |
| ComponentSystem.js | React composition | Native React feature |
| CallbackRenderViewport.js | viewport/RenderViewport.tsx | React hooks for lifecycle |
| SceneOutlinerSync.js | sceneOutliner/SceneOutliner.tsx | React tree component |
| SceneOutlinerControls.js | sceneOutliner/OutlinerControls.tsx | Reusable button components |
| NodeInspector.js | nodeInspector/NodeInspector.tsx | Form state with hooks |
| NodeGraphEditor.js | nodeGraph/NodeGraphEditor.tsx | Canvas ref + hooks |
| RenderToolbar.js | viewport/RenderToolbar.tsx | Button components |
| MenuSystem.js | layout/MenuBar.tsx | Dropdown components |
| KeyboardShortcuts.js | hooks/useKeyboardShortcuts.ts | Single centralized hook |
| LayoutManager.js | CSS Grid + flexbox | Native CSS |
| DebugConsole.js | debug/DebugConsole.tsx | React component |

## Implementation Phases

### Phase 1: Project Setup & Core Infrastructure (Day 1)
1. ✅ Initialize Vite + React + TypeScript project
2. ✅ Setup project structure and folders
3. ✅ Configure Vite for CORS and proxy settings
4. ✅ Port OTOY theme CSS to styled system
5. ✅ Create basic layout components (MainLayout, MenuBar, StatusBar)
6. ✅ Implement LoadingScreen component

### Phase 2: gRPC Communication Layer (Day 1-2)
1. ✅ Port OctaneClient to TypeScript (api/OctaneClient.ts)
2. ✅ Create API endpoint modules (scene, camera, render, nodes)
3. ✅ Setup React Query for API calls
4. ✅ Implement callback streaming hook (useCallbackStream)
5. ✅ Create connection management hook (useOctaneConnection)
6. ✅ Test connectivity with Python proxy

### Phase 3: State Management (Day 2)
1. ✅ Create Zustand stores for:
   - Connection state
   - Scene hierarchy
   - Node selection
   - Render state
   - Node graph state
   - UI state
2. ✅ Implement store actions and selectors
3. ✅ Setup React Query cache configuration

### Phase 4: Render Viewport (Day 2-3)
1. ✅ Implement RenderViewport component
2. ✅ Port canvas rendering logic
3. ✅ Implement mouse drag camera sync
4. ✅ Create ViewportControls (zoom, fit, etc.)
5. ✅ Add ViewportOverlay for stats
6. ✅ Implement RenderToolbar
7. ✅ Test real-time callback streaming

### Phase 5: Scene Outliner (Day 3)
1. ✅ Create SceneOutliner container component
2. ✅ Implement recursive SceneTree component
3. ✅ Create SceneTreeNode with expand/collapse
4. ✅ Add visibility toggles
5. ✅ Implement OutlinerTabs (Scene/LiveDB/LocalDB)
6. ✅ Add OutlinerControls buttons
7. ✅ Connect to scene state store

### Phase 6: Node Inspector (Day 3-4)
1. ✅ Create NodeInspector component
2. ✅ Implement ParameterGroup (collapsible sections)
3. ✅ Create ParameterControl for different types:
   - Numbers (sliders, inputs)
   - Colors (color pickers)
   - Booleans (checkboxes)
   - Strings (text inputs)
   - Enums (dropdowns)
4. ✅ Add QuickAccessButtons
5. ✅ Implement live parameter updates to Octane

### Phase 7: Node Graph Editor (Day 4-5)
1. ✅ Create NodeGraphEditor canvas component
2. ✅ Implement GraphNode visual representation
3. ✅ Create GraphConnection rendering
4. ✅ Add pan and zoom functionality
5. ✅ Implement node selection
6. ✅ Create ContextMenu for node creation
7. ✅ Add node connection logic
8. ✅ Implement node graph state synchronization

### Phase 8: Keyboard Shortcuts & Interactions (Day 5)
1. ✅ Implement useKeyboardShortcuts hook
2. ✅ Define all keyboard shortcuts in one place:
   - Delete: Remove selected nodes
   - Ctrl+D: Toggle debug console
   - Ctrl+C/V: Copy/paste nodes
   - F: Frame selected
   - Space: Play/pause
   - Etc.
3. ✅ Remove duplicate event handlers
4. ✅ Test all interactions

### Phase 9: Menu System (Day 5-6)
1. ✅ Create MenuBar with dropdowns
2. ✅ Implement File menu (Open, Save, Export)
3. ✅ Implement Edit menu (Undo, Redo, Copy, Paste)
4. ✅ Implement Script menu
5. ✅ Implement Module menu
6. ✅ Implement Cloud menu
7. ✅ Implement Window menu
8. ✅ Implement Help menu

### Phase 10: Debug & Polish (Day 6-7)
1. ✅ Create DebugConsole component
2. ✅ Implement performance monitoring
3. ✅ Add error boundaries
4. ✅ Polish animations and transitions
5. ✅ Responsive design testing
6. ✅ Cross-browser testing
7. ✅ Performance optimization

### Phase 11: Testing & Documentation (Day 7)
1. ✅ Test all features against original octaneWeb
2. ✅ Verify UX matches exactly
3. ✅ Document component API
4. ✅ Create README with setup instructions
5. ✅ Final bug fixes

## Code Quality Standards

### TypeScript Usage
```typescript
// Strict typing for all functions
interface SceneNode {
  id: string;
  name: string;
  type: string;
  children: SceneNode[];
  visible: boolean;
}

const renderNode = (node: SceneNode): JSX.Element => {
  // Implementation
};
```

### Component Structure
```typescript
// Consistent component pattern
interface Props {
  // Props interface
}

export const ComponentName: React.FC<Props> = ({ prop1, prop2 }) => {
  // Hooks at top
  const [state, setState] = useState();
  const customHook = useCustomHook();
  
  // Event handlers
  const handleEvent = useCallback(() => {
    // Implementation
  }, [dependencies]);
  
  // Effects
  useEffect(() => {
    // Side effects
  }, [dependencies]);
  
  // Render
  return (
    <div>
      {/* JSX */}
    </div>
  );
};
```

### No Duplicate Code
- Single source of truth for all operations
- Reusable hooks for common logic
- Shared components for repeated UI patterns
- Utility functions for calculations

## Performance Considerations

1. **Memoization**: Use `React.memo()` for expensive components
2. **useCallback**: Prevent unnecessary re-renders
3. **Virtual Scrolling**: For large scene trees
4. **Canvas Optimization**: RequestAnimationFrame for smooth rendering
5. **Lazy Loading**: Code splitting for faster initial load
6. **Zustand**: Minimal re-renders with fine-grained subscriptions

## Testing Strategy

1. **Component Tests**: Test each component in isolation
2. **Integration Tests**: Test component interactions
3. **E2E Tests**: Test complete workflows
4. **gRPC Tests**: Test API communication
5. **Performance Tests**: Monitor FPS and memory

## Migration Path

### Coexistence Strategy
- octaneWeb (original) stays in `octaneWeb/` folder
- octaneWeb2 (React) created in new `octaneWeb2/` folder
- Both use same Python proxy on port 51023
- Can compare side-by-side during development

### Development Workflow
1. Keep octaneWeb running for reference
2. Implement feature in octaneWeb2
3. Compare behavior and UX
4. Iterate until match
5. Move to next feature

## Success Criteria

✅ **Functional Parity**: All features from octaneWeb work in octaneWeb2
✅ **UX Match**: Visual appearance and interactions identical
✅ **Cleaner Code**: Significantly less code, better organized
✅ **No Duplicates**: Single pathway for each operation
✅ **Maintainability**: Easy to understand and modify
✅ **Performance**: Equal or better than original
✅ **Type Safety**: Full TypeScript coverage

## Deliverables

1. ✅ Complete React application in `octaneWeb2/` folder
2. ✅ README.md with setup instructions
3. ✅ Component documentation
4. ✅ Migration guide
5. ✅ Performance comparison report

## Dependencies

### Core
```json
{
  "react": "^18.2.0",
  "react-dom": "^18.2.0",
  "typescript": "^5.0.0",
  "vite": "^5.0.0"
}
```

### State Management
```json
{
  "zustand": "^4.4.0",
  "@tanstack/react-query": "^5.0.0"
}
```

### UI & Styling
```json
{
  "clsx": "^2.0.0",
  "@radix-ui/react-*": "latest" // For accessible UI components
}
```

### Development
```json
{
  "eslint": "^8.0.0",
  "prettier": "^3.0.0",
  "@types/react": "^18.2.0",
  "@types/react-dom": "^18.2.0"
}
```

## Timeline Estimate

- **Total Duration**: 7 days
- **Lines of Code**: ~6,000 lines (50% reduction from original)
- **Components**: ~40 React components
- **Hooks**: ~10 custom hooks
- **Stores**: 6 Zustand stores

## Risk Mitigation

1. **gRPC Compatibility**: Test early and often with proxy
2. **Performance**: Profile regularly during development
3. **UX Differences**: Side-by-side comparison continuously
4. **Browser Support**: Test on Chrome, Firefox, Safari, Edge
5. **Complex Interactions**: Break down into smaller, testable pieces

## Future Enhancements (Post-MVP)

1. Unit tests with Vitest
2. Storybook for component documentation
3. PWA capabilities
4. Offline mode
5. Multi-language support
6. Accessibility (WCAG 2.1 AA)

---

## Summary

This rebuild will create a modern, maintainable React application that matches the current octaneWeb UX while eliminating code duplication, centralizing event handling, and providing a cleaner architecture. The key improvements are:

1. **Single source of truth** for all operations (no duplicate pathways)
2. **Centralized state management** with Zustand (simpler than current EventSystem)
3. **Type safety** with TypeScript
4. **Cleaner code** with React hooks and composition
5. **Better performance** with optimized re-renders
6. **Easier maintenance** with clear component boundaries

The existing gRPC communication and Python proxy will remain unchanged, ensuring the core functionality continues to work seamlessly.
