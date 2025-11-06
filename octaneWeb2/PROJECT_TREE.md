# OctaneWeb2 Project Structure

## Complete Directory Tree

```
octaneWeb2/
├── 📄 Configuration Files
│   ├── package.json              # npm dependencies and scripts
│   ├── package-lock.json         # Locked dependency versions
│   ├── tsconfig.json             # TypeScript compiler config
│   ├── tsconfig.node.json        # TypeScript config for Vite
│   ├── vite.config.ts            # Vite build configuration
│   ├── .gitignore                # Git ignore patterns
│   └── index.html                # HTML entry point
│
├── 📚 Documentation (1,500+ lines)
│   ├── README.md                 # Project overview and quick start
│   ├── PROJECT_SUMMARY.md        # Executive summary (this overview)
│   ├── IMPLEMENTATION_PLAN.md    # 11-phase detailed plan
│   ├── CODE_COMPARISON.md        # Before/after code examples
│   ├── STATUS.md                 # Current progress tracker
│   ├── CHANGELOG.md              # Version history
│   └── PROJECT_TREE.md           # This file
│
├── 🛠️ Scripts
│   └── start.sh                  # Development server startup script
│
├── 📦 Public Assets
│   └── public/
│       └── assets/               # (empty - ready for icons, images)
│
└── 💻 Source Code (392 lines TypeScript)
    └── src/
        │
        ├── 🎨 Styles
        │   └── styles/
        │       └── variables.css  # CSS custom properties (theme)
        │
        ├── 🔷 TypeScript Types
        │   └── types/
        │       └── octane.ts      # SceneNode, Vector3, RenderStats, etc.
        │
        ├── 🌐 API Layer
        │   └── api/
        │       ├── OctaneClient.ts     # Singleton API client
        │       └── endpoints/          # (empty - future endpoint logic)
        │
        ├── 📦 State Management (Zustand)
        │   └── store/
        │       ├── connectionStore.ts  # Connection state
        │       └── renderStore.ts      # Render data & stats
        │
        ├── 🎣 Custom Hooks
        │   └── hooks/                  # (empty - Phase 2+)
        │       ├── (useRenderCallback.ts)      # TODO: WebSocket stream
        │       ├── (useCameraControls.ts)      # TODO: Mouse camera
        │       ├── (useKeyboardShortcuts.ts)   # TODO: Global shortcuts
        │       └── (useSceneSync.ts)           # TODO: Scene updates
        │
        ├── 🧩 React Components
        │   └── components/
        │       │
        │       ├── layout/               # App structure
        │       │   ├── MainLayout.tsx    # 3-panel grid layout
        │       │   ├── MainLayout.css
        │       │   ├── MenuBar.tsx       # Top menu with connection
        │       │   ├── MenuBar.css
        │       │   ├── StatusBar.tsx     # Bottom status bar
        │       │   └── StatusBar.css
        │       │
        │       ├── viewport/             # Render display
        │       │   ├── RenderViewport.tsx
        │       │   └── RenderViewport.css
        │       │
        │       ├── sceneOutliner/        # (empty - Phase 4)
        │       │   ├── (SceneOutliner.tsx)     # TODO: Main component
        │       │   ├── (TreeView.tsx)          # TODO: Tree rendering
        │       │   └── (TreeNode.tsx)          # TODO: Recursive node
        │       │
        │       ├── nodeInspector/        # (empty - Phase 5)
        │       │   ├── (NodeInspector.tsx)     # TODO: Main component
        │       │   └── parameterRenderers/
        │       │       ├── (NumberInput.tsx)   # TODO: Sliders
        │       │       ├── (ColorPicker.tsx)   # TODO: Color select
        │       │       ├── (BooleanToggle.tsx) # TODO: Checkboxes
        │       │       └── (EnumSelect.tsx)    # TODO: Dropdowns
        │       │
        │       ├── nodeGraph/            # (empty - Phase 6)
        │       │   ├── (NodeGraphCanvas.tsx)   # TODO: SVG canvas
        │       │   ├── (GraphNode.tsx)         # TODO: Node rendering
        │       │   ├── (Connection.tsx)        # TODO: Node links
        │       │   └── (ContextMenu.tsx)       # TODO: Right-click menu
        │       │
        │       ├── common/               # (empty - shared UI)
        │       │   ├── (Button.tsx)            # TODO: Reusable button
        │       │   ├── (Input.tsx)             # TODO: Text input
        │       │   ├── (Slider.tsx)            # TODO: Range slider
        │       │   └── (ErrorBoundary.tsx)     # TODO: Error handling
        │       │
        │       └── debug/                # (empty - Phase 8)
        │           ├── (DebugConsole.tsx)      # TODO: Ctrl+D console
        │           └── (LogEntry.tsx)          # TODO: Log display
        │
        ├── 🔧 Utilities
        │   └── utils/                    # (empty - Phase 2+)
        │       ├── (bufferProcessing.ts)       # TODO: HDR/LDR conversion
        │       ├── (cameraUtils.ts)            # TODO: Camera math
        │       ├── (nodeTypeRegistry.ts)       # TODO: Node type definitions
        │       └── (consoleInterceptor.ts)     # TODO: Log capture
        │
        ├── App.tsx                       # Root App component
        └── main.tsx                      # Entry point (ReactDOM.render)
```

---

## Statistics

### Files Created (Phase 1)
- **Configuration**: 7 files (package.json, tsconfig, vite.config, etc.)
- **Documentation**: 7 files (README, PLAN, COMPARISON, STATUS, etc.)
- **Source Code**: 11 files (.tsx, .ts, .css)
- **Total**: 25 files

### Lines of Code (Phase 1)
- **TypeScript/TSX**: 392 lines
- **CSS**: 150 lines
- **Documentation**: 1,500+ lines
- **Configuration**: 100 lines

### Files Planned (Future Phases)
- **Hooks**: ~10 files
- **Components**: ~30 files
- **Utilities**: ~5 files
- **Stores**: ~4 more files
- **Total Target**: ~75 files

---

## Key Directories Explained

### `/src/api/` - API Layer
- **Purpose**: All communication with Octane via proxy
- **Pattern**: Singleton `OctaneClient` class
- **Example**: `await octaneClient.getSceneTree()`

### `/src/store/` - Zustand Stores
- **Purpose**: Global state management
- **Pattern**: Each store handles one domain (connection, render, scene, etc.)
- **Example**: `const isConnected = useConnectionStore(state => state.isConnected)`

### `/src/hooks/` - Custom React Hooks
- **Purpose**: Reusable stateful logic
- **Pattern**: `use` prefix, returns state and handlers
- **Example**: `useRenderCallback()` - WebSocket stream management

### `/src/components/` - React Components
- **Purpose**: UI rendering
- **Pattern**: Each feature in its own folder with styles
- **Structure**:
  - `layout/` - App structure (MenuBar, StatusBar, MainLayout)
  - `viewport/` - Render display
  - `sceneOutliner/` - Scene tree view
  - `nodeInspector/` - Parameter editor
  - `nodeGraph/` - Visual node editor
  - `common/` - Reusable UI components
  - `debug/` - Development tools

### `/src/utils/` - Utility Functions
- **Purpose**: Pure functions, no state or side effects
- **Pattern**: Named exports, TypeScript types
- **Example**: `convertHDRtoImageData(buffer, width, height)`

### `/src/types/` - TypeScript Definitions
- **Purpose**: Shared type definitions
- **Pattern**: Interfaces and types for Octane data structures
- **Example**: `interface SceneNode { id: string; name: string; ... }`

### `/src/styles/` - Global CSS
- **Purpose**: Theme variables and global styles
- **Pattern**: CSS custom properties (variables)
- **Example**: `var(--color-bg-primary)`

---

## Naming Conventions

### Components (PascalCase)
```typescript
// Files
MainLayout.tsx
RenderViewport.tsx
TreeNode.tsx

// Exports
export const MainLayout = () => { ... }
```

### Hooks (camelCase with `use` prefix)
```typescript
// Files
useRenderCallback.ts
useCameraControls.ts
useKeyboardShortcuts.ts

// Exports
export const useRenderCallback = () => { ... }
```

### Stores (camelCase with `Store` suffix)
```typescript
// Files
connectionStore.ts
renderStore.ts
sceneStore.ts

// Exports
export const useConnectionStore = create<ConnectionState>(...);
```

### Utilities (camelCase)
```typescript
// Files
bufferProcessing.ts
cameraUtils.ts

// Exports
export const convertHDRtoImageData = (...) => { ... }
export const calculateCameraPosition = (...) => { ... }
```

### Types (PascalCase)
```typescript
// Interfaces
interface SceneNode { ... }
interface Vector3 { ... }
interface RenderStats { ... }

// Type aliases
type NodeType = 'mesh' | 'light' | 'camera';
```

---

## File Dependencies

### Import Flow (Typical)
```
Component
  ↓ imports
  Hook (custom)
    ↓ imports
    Store (Zustand)
      ↓ updates
    State
  ↓ imports
  API Client
    ↓ calls
  Octane Proxy
    ↓ gRPC
  Octane LiveLink
```

### Example: RenderViewport Component
```typescript
// RenderViewport.tsx
import { useRenderStore } from '@/store/renderStore';     // ← Store
import { useRenderCallback } from '@/hooks/useRenderCallback'; // ← Hook
import './RenderViewport.css';                            // ← Styles

export const RenderViewport = () => {
  const imageData = useRenderStore(state => state.imageData);
  useRenderCallback(); // Start receiving frames
  
  // Render canvas with imageData
};
```

---

## Path Aliases

Configured in `tsconfig.json` and `vite.config.ts`:

```typescript
// Instead of relative paths
import { useRenderStore } from '../../../store/renderStore';

// Use absolute alias
import { useRenderStore } from '@/store/renderStore';
```

All paths starting with `@/` resolve to `src/` directory.

---

## Hot Module Replacement (HMR)

Vite provides instant feedback:

```typescript
// Edit any file:
src/components/layout/MenuBar.tsx

// ⚡ Instant update in browser (no page reload!)
```

Files that trigger HMR:
- `.tsx` / `.ts` - Component/logic changes
- `.css` - Style changes
- `.json` - Config changes (some require restart)

---

## Build Output

### Development
```bash
npm run dev
# Output: http://localhost:42219
# No build artifacts, runs from memory
```

### Production
```bash
npm run build
# Output: dist/
#   ├── index.html
#   ├── assets/
#   │   ├── index-[hash].js
#   │   └── index-[hash].css
```

Optimizations in production build:
- Tree-shaking (remove unused code)
- Minification (compress code)
- Code-splitting (separate chunks)
- Asset hashing (cache busting)

---

## Next Steps

### Phase 2 Files to Create
1. `src/utils/bufferProcessing.ts` - HDR/LDR buffer conversion
2. `src/hooks/useRenderCallback.ts` - WebSocket render stream
3. Update `src/components/viewport/RenderViewport.tsx` - Display frames

### Phase 3 Files to Create
1. `src/hooks/useCameraControls.ts` - Mouse drag camera rotation
2. `src/utils/cameraUtils.ts` - Camera position/target calculations

### Phase 4 Files to Create
1. `src/store/sceneStore.ts` - Scene tree state
2. `src/components/sceneOutliner/SceneOutliner.tsx` - Main component
3. `src/components/sceneOutliner/TreeView.tsx` - Tree rendering
4. `src/components/sceneOutliner/TreeNode.tsx` - Recursive node
5. `src/hooks/useSceneSync.ts` - Scene synchronization

---

## Comparison: Original vs React

### Original octaneWeb
```
octaneWeb/
└── js/                           # 12,592 lines vanilla JS
    ├── components/               # 9 files
    ├── core/                     # 3 files (custom state/events)
    └── utils/                    # 11 files
Total: 23 files, no types, manual DOM
```

### OctaneWeb2 (Target)
```
octaneWeb2/
└── src/                          # ~6,000 lines TypeScript
    ├── components/               # ~30 files (React)
    ├── hooks/                    # ~10 files (custom hooks)
    ├── store/                    # ~6 files (Zustand)
    ├── api/                      # ~3 files (API client)
    ├── utils/                    # ~5 files (pure functions)
    └── types/                    # ~3 files (TypeScript)
Total: ~75 files, full types, React virtual DOM
```

**Result**: 52% less code, better organization, full type safety

---

## Development Workflow

### Start Fresh Session
```bash
cd /workspace/grpcSamples/octaneWeb2
npm install    # If needed
npm run dev    # Start dev server
# Open http://localhost:42219
```

### Make Changes
1. Edit files in `src/`
2. See instant updates (HMR)
3. Check console for errors
4. Test in browser

### Add New Feature
1. Create types in `src/types/`
2. Add API method in `src/api/OctaneClient.ts`
3. Create/update store in `src/store/`
4. Create custom hook in `src/hooks/`
5. Build component in `src/components/`

### Commit Changes
```bash
git add .
git commit -m "feat: add feature name"
```

---

## Success Metrics

### Code Quality
- ✅ TypeScript compiles with zero errors
- ✅ ESLint passes (if configured)
- ✅ No console warnings in browser

### Performance
- ✅ App loads in <2 seconds
- ✅ Renders at 60+ FPS
- ✅ No memory leaks (check DevTools)

### UX
- ✅ Matches original octaneWeb functionality
- ✅ Responsive to user input (<100ms)
- ✅ Handles errors gracefully

---

**Status**: Phase 1 Complete ✅  
**Next**: Phase 2 - Core Rendering (1-2 days)  
**Dev Server**: Running at http://localhost:42219
