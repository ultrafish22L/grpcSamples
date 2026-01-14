# octaneWebR

**Pixel-perfect React/TypeScript UI clone of Octane Render Studio SE with real-time gRPC connectivity**

## 🎯 Project Goal

Clone **Octane Render Studio Standalone Edition's UI/UX exactly**, using the [Octane SE Manual](https://docs.otoy.com/standaloneSE/CoverPage.html) as the reference specification. Every visual element and interaction should match Octane SE, powered by real-time gRPC API communication with Octane LiveLink.

**See [WORKFLOW.md](./WORKFLOW.md) for detailed development process.**

---

## 🚀 Quick Start

```bash
cd /workspace/project/grpcSamples/octaneWebR
npm install    # First time only
npm run dev    # Start dev server with embedded gRPC proxy
```

Open **http://localhost:43929** (or port shown in terminal)

**Prerequisites**: Octane Render with LiveLink enabled (Help → LiveLink in Octane menu)

---

## 📊 Current Status

**Production-Ready Core** ✅ - All essential features working, advanced features in progress

### What's Working

- ✅ **Real-time Scene Management** - Interactive scene outliner with hierarchical tree view
- ✅ **Node Graph Editor** - ReactFlow v12-based visual node graph with:
  - ✅ Node creation via right-click context menu
  - ✅ Pin connections/disconnections synced to Octane
  - ✅ Edge reconnections with drag-and-drop
  - ✅ Node/edge deletion propagated to Octane
  - ✅ Proper edge colors from pin types
  - ✅ Box selection with Shift multi-select
  - ✅ Search dialog (Ctrl+F) for nodes and pins
  - ✅ Copy/Paste nodes (Ctrl+C/Ctrl+V) with connections preserved (NEW!)
  - ✅ Connection Cutter (Ctrl+Drag) to cut multiple edges at once (NEW!)
  - ✅ Multi-Connect (Ctrl+Connect) to connect multiple selected nodes (NEW!)
- ✅ **Node Inspector** - View and edit node properties with real-time Octane sync
- ✅ **Parameter Editing** - All types supported (bool, int, float, vectors, colors, enums, strings)
- ✅ **Live Rendering** - Real-time callback-based viewport with camera controls
- ✅ **Camera Controls** - Mouse orbit/pan/zoom synced to Octane
- ✅ **Menu System** - File/Edit/View/Window/Help menus with file dialogs
- ✅ **Professional UI** - OTOY-branded dark theme with responsive design
- ✅ **Type Safety** - Full TypeScript support with auto-generated protobuf types
- ✅ **Embedded Proxy** - Vite plugin provides gRPC-Web proxy (no separate server process)

### In Progress / Roadmap

- ⏳ **Material Database** - Live DB and Local DB tabs (UI exists, content not implemented)
- ⏳ **Render Toolbar** - UI complete, most actions need API integration
- 📋 **Advanced Features** - See `OCTANE_STANDALONE_IMPLEMENTATION_PLAN.md` for complete roadmap

---

## 📚 Documentation

- **[WORKFLOW.md](./WORKFLOW.md)** - Development workflow and best practices ⭐
- **[QUICKSTART.md](./QUICKSTART.md)** - Setup instructions and usage guide
- **[OVERVIEW.md](./OVERVIEW.md)** - Architecture overview and technology stack
- **[OCTANE_API_REFERENCE.md](./OCTANE_API_REFERENCE.md)** - gRPC API reference and patterns
- **[OCTANE_STANDALONE_IMPLEMENTATION_PLAN.md](./OCTANE_STANDALONE_IMPLEMENTATION_PLAN.md)** - Feature roadmap organized by Octane SE manual sections

---

## 🏗️ Architecture

```
Browser (React App) → Vite Dev Server (gRPC-Web Plugin) → Octane LiveLink (127.0.0.1:51022)
```

**Technology Stack**:
- **React 18** + **TypeScript 5.6** + **Vite 6**
- **ReactFlow v12** (`@xyflow/react`) - Node graph editor
- **gRPC-Web** - Browser-compatible gRPC protocol
- **Custom CSS** - OTOY-branded styling (no framework dependencies)

**Why embedded proxy?** Browsers cannot natively speak gRPC (HTTP/2 binary protocol). The Vite plugin acts as a transparent gRPC-Web proxy - this is the industry-standard pattern for browser-based gRPC clients.

---

## 🎯 Recent Achievements

- ✅ **2025-01-21**: Implemented 3 advanced Node Graph Editor features per Octane SE manual
  - **Copy/Paste (Ctrl+C/Ctrl+V)**: Copy selected nodes with connections preserved, paste creates new instances via API
  - **Connection Cutter (Ctrl+Drag)**: Hold Ctrl and drag to cut multiple edges at once with visual red line feedback
  - **Multi-Connect (Ctrl+Connect)**: Select multiple nodes, hold Ctrl while connecting to connect all selected nodes
- ✅ **2025-01-21**: Implemented Search Dialog (Ctrl+F) per Octane SE manual
  - Real-time search for node names, types, and pin names
  - Click to select individual node, or Select All for multiple
  - Keyboard shortcuts: Enter to select all, Escape to close
  - Portal rendering with auto-focus on input field
- ✅ **2025-01-21**: Implemented Box Selection and Multi-Select
  - Drag in empty space to create selection box
  - Shift key adds nodes to existing selection
  - Ctrl+click toggles individual node selection
- ✅ **2025-01-21**: Node context menu styling cleanup (removed emoji icons)
- ✅ **2025-01-21**: Major documentation updates to prevent feature hallucination
- ✅ **2025-01-20**: Fixed pin connections not propagating to Octane
  - `onConnect` now calls `client.connectPinByIndex()` for new connections
  - `onReconnect` implements full disconnect-then-connect sync
  - Edge operations properly synchronized with Octane API
- ✅ **2025-01-19**: Fixed React duplicate key warnings in SceneOutliner
- ✅ **2025-01-19**: Fixed node deletion API integration across all components
- ✅ **2025-01-12**: Fixed edge reconnection - destroy connections when dropped on empty space

---

## 🔧 Development

**Build for production**:
```bash
npm run build
```

**Type check only**:
```bash
npm run type-check
```

**Run development server with hot reload**:
```bash
npm run dev
```

---

## 📝 Notes

- **Real Octane Only**: Never use mock or simulated data - only real live connection with Octane LiveLink service
- **Proto Verification**: Always verify API method names in proto files (`/grpcSamples/octaneProxy/generated/*_pb2_grpc.py`) before implementing API calls
- **ReactFlow v12**: Uses new package name `@xyflow/react` (not the old `reactflow` package) with best practices for edge interactions

---

## 🆘 Troubleshooting

**Connection Issues**:
- Ensure Octane is running
- Enable LiveLink: Help → LiveLink in Octane menu
- Check port 51022 is accessible

**Health Check**:
```bash
curl http://localhost:43929/api/health | python -m json.tool
```

**Expected**: `"octane": "connected"` when Octane is running with LiveLink enabled

---

**License**: OTOY © 2025
