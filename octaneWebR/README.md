# octaneWebR

**React/TypeScript UI clone of Octane Render Standalone Edition** with real-time gRPC API integration.

**Repository**: https://github.com/ultrafish22L/grpcSamples  
**Manual Reference**: [Octane SE Manual](https://docs.otoy.com/standaloneSE/CoverPage.html)

---

## Quick Start

```bash
# 1. Start Octane with LiveLink enabled (port 51022)
# 2. Install and run
git clone https://github.com/ultrafish22L/grpcSamples.git
cd grpcSamples/octaneWebR
npm install
npm run dev
# 3. Open http://localhost:43930
```

See [QUICKSTART.md](./QUICKSTART.md) for details.

---

## Current Status (~30% Octane SE Feature Parity)

### ✅ Working Features

**Node Graph Editor** (ReactFlow v12)
- 755+ node types across 25 categories (right-click menu)
- Pin connections with drag-and-drop (synced to Octane)
- Node operations: Copy/Paste (Ctrl+C/V), Delete, Duplicate
- Selection: Click, box select, Shift multi-select
- Connection Cutter: Ctrl+Drag to cut edges
- Multi-Connect: Ctrl+Connect to wire multiple nodes
- Search: Ctrl+F for node/pin search
- Context menus: Node and canvas right-click
- Minimap with viewport indicator
- Auto edge coloring by pin type

**Scene Outliner** (Tree View)
- Hierarchical scene tree from Octane
- Expand/collapse with persistent state
- Visibility toggles per node
- Selection sync with Node Graph
- Type-specific icons
- LiveDB tab: Online material browser
- LocalDB tab: Local materials/groups

**Node Inspector** (Parameter Editor)
- Real-time editing synced to Octane
- All parameter types: Boolean, Numbers, Vectors, Colors, Enums, Strings
- Collapsible parameter groups
- Right-click context menu

**Render Viewport**
- Real-time image streaming via callbacks
- Camera controls: Orbit, pan, zoom (synced)
- HDR display
- Viewport toolbar: Play/pause, resolution, render mode
- Picking tools: Material, Object, Focus, Camera Target, White Balance

**Menu System** (100% Octane SE match)
- File: New, Open, Save, Package, Preferences
- Edit: Undo, Redo, Cut, Copy, Paste, Delete, Select All
- Script: Batch Rendering, Daylight Animation, Turntable Animation
- View: Panel toggles, Refresh Scene (F5)
- Window: Material Database, Reset Layout, Fullscreen (F11)
- Help: Documentation, Shortcuts, Report Bug, About

**Keyboard Shortcuts**
- Ctrl+N: New scene
- Ctrl+O: Open scene
- Ctrl+S: Save scene
- Ctrl+Z/Y: Undo/Redo
- Ctrl+C/V: Copy/Paste
- Ctrl+F: Search
- Delete: Delete selected
- F5: Refresh scene
- F11: Fullscreen

### ⏳ Missing Features (High Priority)

See [CODE_REVIEW.md](./CODE_REVIEW.md) for complete task list.

**P1 - User Experience**
- Context menu handlers (currently placeholders)
- Cross-panel event system ("Show in Graph Editor")
- Enhanced clipboard (preserve connections/positions)

**P2 - Feature Parity**
- Material Database search/filtering
- Node Graph grouping/auto-layout
- Viewport region rendering/LUT previews

---

## Architecture

**Stack**: React 18 + TypeScript 5.6 + Vite 6  
**Node Graph**: ReactFlow v12 (@xyflow/react)  
**Styling**: Custom CSS (Octane SE dark theme)  
**Communication**: gRPC-Web via embedded Vite proxy

### System Flow

```
Browser (React App)
  └─ UI Components (NodeGraph, SceneOutliner, NodeInspector, RenderViewport)
  └─ OctaneClient (gRPC-Web)
      └─ HTTP/WebSocket
          └─ Vite Dev Server (gRPC Proxy)
              └─ Octane Render (localhost:51022)
```

### Key Design Decisions

1. **ReactFlow v12** - Industry-standard node graph library (replaced 956-line custom SVG)
2. **TypeScript Strict** - Compile-time errors, auto-complete from proto types
3. **No UI Framework** - Custom CSS for pixel-perfect Octane SE matching
4. **Real API Only** - No mocks, forces adherence to Octane behavior

### File Structure

```
octaneWebR/
├── client/src/
│   ├── App.tsx                     # Root component, 4-panel layout
│   ├── services/OctaneClient.ts    # gRPC client, scene management
│   ├── components/
│   │   ├── NodeGraph/              # Node graph editor (ReactFlow)
│   │   │   ├── NodeGraphEditorNew.tsx
│   │   │   ├── OctaneNode.tsx      # Custom node component
│   │   │   ├── NodeContextMenu.tsx
│   │   │   └── SearchDialog.tsx
│   │   ├── SceneOutliner.tsx       # Tree view
│   │   ├── NodeInspector.tsx       # Parameter editor
│   │   ├── CallbackRenderViewport.tsx  # Render display
│   │   └── MenuBar.tsx             # Top menu
│   ├── hooks/
│   │   ├── useOctane.tsx           # Octane client context
│   │   └── useKeyboardShortcuts.ts # Global shortcuts
│   ├── constants/
│   │   ├── NodeTypes.ts            # 755 node type definitions
│   │   └── OctaneTypes.ts          # Type mappings
│   └── utils/
│       ├── OctaneIconMapper.ts     # 636 node icons
│       └── EventEmitter.ts         # Cross-component events
├── server/proto/                   # gRPC proto definitions
└── vite-plugin-octane-grpc.ts      # Embedded proxy plugin
```

---

## Documentation

- **[README.md](./README.md)** - Project overview (this file)
- **[CODE_REVIEW.md](./CODE_REVIEW.md)** - Current priorities and task list
- **[WORKFLOW.md](./WORKFLOW.md)** - Development guidelines
- **[QUICKSTART.md](./QUICKSTART.md)** - Setup guide

---

## Development

```bash
# Build (TypeScript + Vite)
npm run build

# Dev server (hot reload)
npm run dev

# Type check only
npx tsc --noEmit

# Generate proto types
npm run generate:proto
```

**Requirements**: Node.js 18+, Octane with LiveLink enabled

See [WORKFLOW.md](./WORKFLOW.md) for development process.

---

## Testing

### Manual Testing
1. Start Octane with LiveLink
2. Run `npm run dev`
3. Open http://localhost:43930
4. Test features in browser

### Verification Checklist
- ✅ Scene tree loads in Scene Outliner
- ✅ Node graph displays in Node Graph Editor
- ✅ Create node via right-click menu
- ✅ Connect pins with drag-and-drop
- ✅ Edit parameters in Node Inspector
- ✅ Changes sync to Octane in real-time

**Debugging**: Check browser console (F12) and `octaneWebR_client.log`

---

## Troubleshooting

**Cannot connect to Octane?**
- Verify Octane is running
- Enable LiveLink (Help → LiveLink)
- Check port 51022 is accessible

**Build errors?**
- Check TypeScript version ≥ 5.3
- Run `npm run generate:proto`
- Clear cache: `rm -rf node_modules/.vite && npm install`

**Changes not syncing?**
- Check browser console for errors
- Verify Octane scene is not locked
- Restart both Octane and dev server

---

## Contributing

1. Read [WORKFLOW.md](./WORKFLOW.md) for development process
2. Wait for task assignment (see [CODE_REVIEW.md](./CODE_REVIEW.md))
3. Verify feature in [Octane SE Manual](https://docs.otoy.com/standaloneSE/CoverPage.html)
4. Check proto files for API methods
5. Implement with TypeScript/React best practices
6. Build must pass (`npm run build`)
7. Commit and push (if authorized)

**Always wait for task assignment - never start without approval**

---

## License

Proprietary - All rights reserved

**OctaneRender® and OTOY® are registered trademarks of OTOY Inc.**

---

## Project Statistics

- **React Components**: 45 files
- **Lines of Code**: ~8,500 TypeScript/TSX
- **Node Types Supported**: 755+
- **Node Icons**: 636 mapped
- **Completion**: ~30% of Octane SE features

---

## Resources

- [React 18 Docs](https://react.dev/)
- [TypeScript Handbook](https://www.typescriptlang.org/docs/)
- [ReactFlow Docs](https://reactflow.dev/)
- [Vite Guide](https://vitejs.dev/guide/)
- [Octane SE Manual](https://docs.otoy.com/standaloneSE/)
