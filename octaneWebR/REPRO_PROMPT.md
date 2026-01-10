# REPRO_PROMPT: octaneWebR Development Context

**Last Updated**: 2025-01-21  
**Status**: ✅ Production-Ready Core Complete  

---

## 🎯 Project Overview

**octaneWebR** is a React + TypeScript port of octaneWeb (vanilla JS), providing a browser-based interface for OTOY Octane Render via LiveLink gRPC API.

**Tech Stack**: React 18, TypeScript 5.6, Vite 6, ReactFlow, gRPC-Web  
**Architecture**: Single Vite dev server with embedded gRPC proxy (no separate backend)  
**Location**: `/workspace/project/grpcSamples/octaneWebR`

---

## ✅ Completed Features

### Core Functionality (Production-Ready)
- ✅ **Scene Outliner**: Hierarchical tree with expand/collapse, node selection, type icons
- ✅ **Node Inspector**: Real-time parameter editing via `ApiItem.setByAttrID`
  - All types: bool, int, float, vectors (2/3/4), colors, enums, strings
  - Enum dropdowns with proper value/label mapping
  - Color pickers for RGB values
  - Vector inputs with individual components
- ✅ **Node Graph Editor**: ReactFlow-based with drag-and-drop, zoom, pan, minimap
  - Custom OctaneNode components with pin visualization
  - Bezier connections between nodes
  - Context menus for node operations
- ✅ **Live Render Viewport**: Real-time OnNewImage callbacks
  - Mouse camera controls: orbit (drag), pan (Shift+drag), zoom (scroll)
  - Camera synchronization with Octane (setCameraPosition/setCameraTarget)
  - HDR/LDR format detection with proper buffer handling
  - Actual-size display with scrollbars
- ✅ **Connection Status**: Top-right indicator (Connected/Disconnected)
- ✅ **Menu System**: File/Edit/View/Window/Help menus with file dialogs (partial)

### Recent Improvements (Last 5 Commits)
- `705e325c` - Enum dropdown support for NT_ENUM parameters
- `b03b7d36` - Real-time parameter editing with setByAttrID
- `ea662c3d` - Camera panning X/Y fix (no Z depth)
- `7466dd01` - Canvas display fix (explicit pixel dimensions)
- `59755ac4` - Actual-size viewport with scrollbars

---

## ⏳ Not Yet Ported from octaneWeb

### High Priority
1. **Render Toolbar Actions**: ~25 actions need API integration
   - Start/Stop/Pause/Restart rendering
   - Clay mode, sub-sampling, render priority
   - Picking modes (focus, white balance, material, object)
   - Gizmo controls (translate, rotate, scale)
   - Viewport/resolution lock
   - Save/copy render outputs

2. **Material Database**: Live DB and Local DB tabs are placeholders
   - Online community materials browser
   - Local material package loader

3. **Menu System**: Only 13/40+ menu items implemented
   - Missing: cloud.*, module.*, script.* menus
   - File operations need full Octane API integration

### Medium Priority
4. **Toast Notifications**: User feedback system (success/error/info)
5. **Scene File Loading**: File dialog works, loading not wired to API
6. **Render Statistics**: Real-time updates (samples, time, GPU, memory)
7. **Camera Presets**: Front/Back/Top/Bottom/Left/Right views

### Low Priority
8. **Keyboard Shortcuts**: System not implemented (Ctrl+S, Ctrl+Z, etc.)

---

## 🚀 Quick Commands

```bash
# Navigate to project
cd /workspace/project/grpcSamples/octaneWebR

# Install dependencies
npm install

# Start dev server (one command - includes gRPC proxy)
npm run dev

# Build for production
npm run build

# TypeScript type check only
tsc --noEmit

# Regenerate protobuf types
npm run proto:generate
```

**Dev Server**: http://localhost:43929 (or next available port)  
**Health Check**: `curl http://localhost:43929/api/health`

---

## 📁 Key Files

### Components
```
client/src/components/
├── MenuBar.tsx                   # File/Edit/View/Window/Help menus
├── SceneOutliner.tsx             # Left panel - scene tree (Scene/Live DB/Local DB tabs)
├── NodeInspector.tsx             # Right panel - property editor with real-time updates
├── NodeInspectorControls.tsx     # Parameter input controls (all types)
├── CallbackRenderViewport.tsx    # Center panel - live rendering with camera controls
├── RenderToolbar.tsx             # Render controls and stats (partial)
├── NodeGraph/
│   ├── NodeGraphEditorNew.tsx    # ReactFlow-based graph editor
│   └── OctaneNode.tsx            # Custom node component with pins
└── ConnectionStatus.tsx          # Top-right status indicator
```

### Core Services
```
client/src/
├── services/OctaneClient.ts      # Core gRPC client with API methods
├── hooks/useOctane.tsx           # React hooks for Octane integration
├── types/scene.ts                # TypeScript type definitions
├── constants/OctaneTypes.ts      # Octane node/attribute type constants
└── utils/
    ├── OctaneIconMapper.ts       # Node type to icon mapping
    └── EventEmitter.ts           # Event system for client communication
```

### Build & Config
```
vite.config.mts                   # Vite config with gRPC plugin
vite-plugin-octane-grpc.ts        # Custom gRPC-Web proxy plugin
tsconfig.json                     # TypeScript config
server/proto/*.proto              # Octane API definitions
server/generated/*.ts             # Auto-generated TypeScript types
```

---

## 🔍 Key Patterns

### Octane API Response Structures
```typescript
// Most methods: {result: {handle, type}}
ApiProjectManager.rootNodeGraph() → {result: {handle: "1000000", type: "ApiRootNodeGraph"}}
ApiItem.name() → {result: "teapot.obj"}

// getOwnedItems: {list: {handle, type}}
ApiNodeGraph.getOwnedItems() → {list: {handle: "1000001", type: "ApiItemArray"}}

// getByAttrID: {<type>_value: X, value: "<type>_value"}
ApiItem.getByAttrID() → {float_value: 36.0, value: "float_value"}
```

### Making API Calls
```typescript
const { client, isConnected } = useOctane();

const response = await client.callApi('ApiItem', 'name', {
  handle: nodeHandle,
  type: 16  // ApiItem type code
});
```

### Setting Parameter Values
```typescript
// In NodeInspector.tsx
const handleValueChange = async (value: any, attrType: number) => {
  await client.callApi('ApiItem', 'setByAttrID', {
    handle: node.handle,
    type: node.type,
    attrID: node.attrInfo.attrID,
    value: convertValueForOctane(value, attrType)
  });
};
```

---

## 🐛 Debugging

### Connection Issues
- Ensure Octane running with LiveLink enabled (Help → LiveLink in Octane)
- Check Octane listening on 127.0.0.1:51022
- Health check: `curl http://localhost:43929/api/health`

### TypeScript Errors
- Regenerate types: `npm run proto:generate`
- Check `server/generated/` for updated definitions

### Browser Console
- Look for 📤 (request) and ✅ (success) API call markers
- Check for JavaScript errors on load
- React DevTools for component inspection

---

## 💡 Development Guidelines

### Task Assignment Protocol
1. ✅ Confirm understanding of current state
2. ✅ Acknowledge pending tasks
3. ⏸️ **WAIT for user to assign specific task**
4. 🚫 Never start work without approval

### Code Quality
- Maintain TypeScript type safety (avoid `any` unless necessary)
- Follow patterns from octaneWeb reference (`/workspace/project/grpcSamples/octaneWeb/`)
- Match octaneWeb UI/UX where possible
- Add comments for complex logic
- Keep debug logging during development

### Testing Workflow
1. TypeScript check: `tsc --noEmit` or `npm run build`
2. Start dev server: `npm run dev`
3. Check terminal logs for errors
4. Check browser console for JavaScript errors
5. Test with live Octane if available

### Git Workflow
- Branch: `main`
- Commit messages: Descriptive, explain what and why
- Review staged changes: `git diff --cached`
- Push after each completed task

---

## 📚 Reference Documentation

### Related octaneWeb Files (Original Implementation)
Located in `/workspace/project/grpcSamples/octaneWeb/`:
- `js/components/*.js` - Component reference implementations
- `js/utils/GenericNodeRenderer.js` - Parameter rendering patterns
- `css/components.css` - Styling reference
- `js/app.js` - Main application structure

### Additional Docs
- **OVERVIEW.md** - Complete project architecture and features
- **QUICKSTART.md** - Setup and run instructions
- Octane Standalone Manual: https://docs.otoy.com/standaloneSE/CoverPage.html

---

## ✅ Ready for Task Assignment

Current state: Development server can be started, all core features working, ready for next feature implementation.

**What's next?** Awaiting task assignment from list above.
