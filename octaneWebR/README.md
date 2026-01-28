# octaneWebR

**Modern web-based UI for Octane Render Studio with real-time gRPC integration**

A React/TypeScript application that provides a browser-based interface for Octane Render, communicating with Octane via the gRPC LiveLink API.

---

## 🎯 Overview

octaneWebR is a web application that replicates the Octane Render Studio Standalone Edition interface, allowing users to:
- Edit Octane scenes through an interactive node graph
- Inspect and modify node parameters in real-time
- View live render output with interactive viewport
- Browse and manage scene hierarchies
- Access LiveDB and LocalDB material libraries

All operations communicate directly with Octane Render via the LiveLink gRPC API—no mocking or simulation.

---

## 🚀 Quick Start

See **[QUICKSTART.md](./QUICKSTART.md)** for detailed setup instructions.

### Prerequisites
- **Octane Render** installed and running
- **LiveLink enabled** in Octane (Help → LiveLink menu)
- **Node.js 18+** installed

### Launch Application
```bash
npm install              # First time only
npm run dev              # Start development server
```

Open **http://localhost:57341** in your browser.

**Connection**: Application connects to Octane at `localhost:51022` (LiveLink default port).

---

## ✨ Features

### Core Components

#### **Node Graph Editor**
ReactFlow-based node graph editor with real-time Octane synchronization:
- Create nodes via right-click context menu (755+ node types, 25 categories)
- Connect pins with drag-and-drop (automatic edge coloring by pin type)
- Multi-select, copy/paste, duplicate, delete operations
- Connection cutter tool (Ctrl+Drag to cut multiple connections)
- Node search dialog (Ctrl+F for instant search)
- Minimap navigation and context menus

#### **Scene Outliner**
Hierarchical tree view of the Octane scene:
- Expandable/collapsible scene tree with type-specific icons
- Visibility toggles and bidirectional selection sync
- LiveDB tab: Browse/download materials from OTOY library
- LocalDB tab: Access locally saved materials and node groups

#### **Node Inspector**
Real-time parameter editor with complete type support:
- Boolean checkboxes, numeric inputs (int/float), vector inputs
- Color pickers (RGB/RGBA), enum dropdowns, text fields
- **Node type dropdown** for non-end nodes (replace current node with compatible type)
- Collapsible parameter groups for organized UI
- Instant synchronization with Octane

#### **Render Viewport**
Live render output with interactive controls:
- Real-time image streaming via Octane callback API
- Camera controls (orbit, pan, zoom) synced to Octane
- HDR display support, resolution and render mode controls
- Interactive picker tools: Material, Object, Focus, Camera Target, White Balance

### Application Features

#### **Menu System**
Complete menu bar matching Octane SE:
- **File**: New, Open, Save, Package, Render State, Preferences
- **Edit**: Undo, Redo, Cut, Copy, Paste, Delete, Select All
- **Script**: Batch Rendering, Daylight/Turntable Animation
- **View**: Panel visibility, Refresh Scene (F5)
- **Window**: Material Database, Reset Layout, Fullscreen (F11)
- **Help**: Documentation, Shortcuts, Report Bug, About

#### **Keyboard Shortcuts**
Platform-aware shortcuts (Ctrl on Windows/Linux, Cmd on macOS):
- `Ctrl+N` - New scene
- `Ctrl+O` - Open scene
- `Ctrl+S` - Save scene
- `Ctrl+Shift+S` - Save As
- `F5` - Refresh scene
- `F11` - Fullscreen

#### **Infrastructure**
- TypeScript with strict type checking (no 'any' types)
- Embedded gRPC-Web proxy (no separate server needed)
- CSS custom properties theme system (Octane SE dark theme)
- Hot module replacement (HMR) for instant updates
- Cross-browser compatible (Chrome, Firefox, Edge, Safari)

---

## 🏗️ Architecture

### Technology Stack
- **Frontend**: React 18 + TypeScript + Vite
- **Node Graph**: ReactFlow v12 (custom nodes and edges)
- **State Management**: Zustand (global state)
- **Communication**: gRPC-Web via embedded proxy
- **Styling**: CSS Modules + CSS Variables (theme system)

### Service Layer
octaneWebR uses a modular service architecture:

```
services/
├── octane/
│   ├── ApiService.ts          - Core gRPC API operations
│   ├── BaseService.ts         - Shared service functionality
│   ├── CameraService.ts       - Camera and viewport controls
│   ├── ConnectionService.ts   - WebSocket connection management
│   ├── DeviceService.ts       - Device and system operations
│   ├── MaterialDatabaseService.ts - LiveDB/LocalDB access
│   ├── NodeService.ts         - Node CRUD operations
│   ├── RenderService.ts       - Render control and streaming
│   ├── RenderExportService.ts - Render export operations
│   ├── SceneService.ts        - Scene tree and node operations
│   ├── ViewportService.ts     - Viewport state management
│   ├── index.ts               - Service exports
│   └── types.ts               - Shared type definitions
└── OctaneClient.ts            - Main API facade
```

All services extend `BaseService` which provides:
- Event emitter for UI synchronization
- Consistent error handling
- Centralized connection state

### gRPC Integration
- **Vite Plugin**: `vite-plugin-octane-grpc.ts` provides embedded proxy
- **Proto Generation**: TypeScript types auto-generated from .proto files
- **Streaming**: WebSocket-based callback streaming for render updates
- **Type Safety**: Full TypeScript coverage of gRPC API

### Styling & Theming
octaneWebR uses a pure CSS variable-based theme system:

```
client/src/styles/
├── octane-theme.css      # Theme variables only (:root)
├── app.css               # App-level UI (menu, panels, status bar)
├── scene-outliner.css    # Scene outliner and tree view
├── viewport.css          # Viewport, canvas, render toolbar
├── node-graph.css        # Node graph editor and context menus
└── node-inspector.css    # Node inspector and parameter controls
```

**Theme System**:
- `octane-theme.css` contains **only** CSS custom properties (134 variables)
- All colors, spacing, typography defined as `--octane-*` variables
- Matches official Octane SE dark theme
- Component CSS files use `var(--octane-*)` references
- Alternative themes can be created by copying and modifying theme variables

---

## 📂 Project Structure

```
octaneWebR/
├── client/                           # React frontend
│   ├── src/
│   │   ├── components/               # React components
│   │   │   ├── CallbackRenderViewport/ # Live render viewport
│   │   │   ├── NodeGraph/            # Node graph editor (ReactFlow)
│   │   │   ├── SceneOutliner/        # Scene tree viewer
│   │   │   ├── NodeInspector/        # Parameter editor
│   │   │   ├── RenderToolbar/        # Render controls
│   │   │   ├── MenuBar/              # Top menu bar
│   │   │   ├── MaterialDatabase/     # LiveDB/LocalDB browser
│   │   │   ├── dialogs/              # Modal dialogs
│   │   │   └── UI/                   # Shared UI components
│   │   ├── services/                 # Business logic layer
│   │   │   ├── octane/               # Octane gRPC services
│   │   │   └── OctaneClient.ts       # Main API facade
│   │   ├── hooks/                    # React hooks
│   │   ├── utils/                    # Helper functions
│   │   ├── constants/                # Enums and constants (NodeTypes, etc.)
│   │   ├── config/                   # Application configuration
│   │   ├── types/                    # TypeScript type definitions
│   │   ├── commands/                 # Command handlers
│   │   ├── styles/                   # CSS stylesheets (theme + components)
│   │   ├── App.tsx                   # Root component
│   │   └── main.tsx                  # Application entry point
│   ├── public/                       # Static assets
│   │   └── icons/                    # Node type icons (PNG)
│   └── index.html                    # HTML template
├── server/                           # gRPC proxy server
│   ├── proto/                        # Compiled proto files
│   └── src/
│       ├── grpc/client.ts            # gRPC client wrapper
│       ├── api/websocket.ts          # WebSocket server
│       ├── services/callbackManager.ts # Callback streaming
│       └── index.ts                  # Server entry point
├── scripts/                          # Build and utility scripts
├── package-for-dist/                 # Distribution packaging scripts
├── vite-plugin-octane-grpc.ts        # Vite plugin (embedded proxy)
├── vite.config.mts                   # Vite configuration
├── tsconfig.json                     # TypeScript configuration
├── package.json                      # Dependencies and scripts
├── README.md                         # This file
├── QUICKSTART.md                     # Setup guide
└── DEVELOPMENT.md                    # Development guide & architecture
```

---

## 🛠️ Development

### Build Commands
```bash
# Development server with hot reload
npm run dev

# Production build
npm run build

# Type check only (no build)
npx tsc --noEmit

# View build output
ls -lh dist/client/
```

### Key Files
- **`client/src/services/OctaneClient.ts`** - Main gRPC API wrapper
- **`client/src/components/NodeGraph/NodeGraphEditor.tsx`** - Node graph editor (1500+ lines)
- **`client/src/components/NodeGraph/OctaneNode.tsx`** - Custom ReactFlow node component
- **`vite-plugin-octane-grpc.ts`** - Vite plugin providing embedded gRPC proxy

### Code Organization
- **Services**: Business logic separated from UI components
- **Components**: React components with clear single responsibility
- **Hooks**: Reusable React hooks for common patterns
- **Utils**: Pure functions for data transformation and formatting
- **Constants**: Centralized enums, icon mappings, node types

---

## 🧪 Testing

### Manual Testing
```bash
# 1. Start Octane with LiveLink enabled (Help → LiveLink menu)
# 2. Start octaneWebR
npm run dev

# 3. Open http://localhost:57341 in browser
# 4. Check browser console for connection logs:
#    ✅ "Connected to Octane"
#    ✅ "Scene tree loaded"
#    ✅ No errors

# 5. Test core features:
#    - Node Graph: Right-click → Create node
#    - Connections: Drag from output pin to input pin
#    - Selection: Click nodes, Shift-click for multi-select
#    - Scene Outliner: Expand/collapse tree
#    - Node Inspector: Edit parameter values
#    - Viewport: Camera orbit/pan/zoom
```

### Health Check
```bash
curl http://localhost:57341/api/health | python -m json.tool
```

**Expected Response**:
```json
{
  "status": "ok",
  "octane": "connected",
  "timestamp": 1737504000000
}
```

---

## 🆘 Troubleshooting

### Connection Issues
**Symptom**: "Cannot connect to Octane" error

**Solutions**:
1. Ensure Octane is running
2. Enable LiveLink: **Help → LiveLink** in Octane menu
3. Check Octane LiveLink port (default: `51022`)
4. Verify no firewall blocking port `51022`
5. Try restarting Octane

### Build Errors
**Symptom**: `npm run build` fails with TypeScript errors

**Solutions**:
1. Check error messages for specific file/line
2. Ensure all imports are correct
3. Verify proto files exist: `ls -la server/proto/`
4. Clear cache: `rm -rf node_modules dist && npm install`

### Runtime Errors
**Common Issues**:
- **"Cannot read property of undefined"** → Scene not loaded, click Refresh
- **"API call failed"** → Check method name in proto files
- **"WebSocket closed"** → Octane disconnected, restart Octane
- **"Invalid handle"** → Node deleted, refresh scene tree

### WebSocket Connection
**Symptom**: WebSocket warnings in browser console on page refresh

**Fix**: octaneWebR includes a 50ms delay in the WebSocket onopen handler to handle browser timing edge cases. Connection should be automatic and silent.

**Debug**:
1. Check browser console for `✅ WebSocket connected` message
2. Verify `readyState: 1 (OPEN)` in debug logs
3. Confirm `Sent subscribe message to WebSocket` appears

---

## 📚 Documentation

### Core Documentation
- **[README.md](./README.md)** - This file (project overview and features)
- **[QUICKSTART.md](./QUICKSTART.md)** - First-time setup guide with copy-paste commands
- **[DEVELOPMENT.md](./DEVELOPMENT.md)** - Development guide with code patterns and architecture
- **[AGENTS.md](./AGENTS.md)** - AI assistant memory (always-loaded essentials)
- **[CHANGELOG.md](./CHANGELOG.md)** - Version history (Keep a Changelog format)
- **[.openhands/skills/](./.openhands/skills/)** - On-demand domain knowledge for AI assistants

### External Resources
- [Octane SE Manual](https://docs.otoy.com/standaloneSE/) - Complete UI reference
- [React 18 Docs](https://react.dev/) - Component patterns
- [ReactFlow v12 Docs](https://reactflow.dev/) - Node graph library
- [Vite Guide](https://vitejs.dev/guide/) - Build tool

---

## 📊 Project Statistics

- **Code**: ~18,000 lines of TypeScript/TSX
- **Components**: 30+ React components
- **Services**: 8 modular gRPC service wrappers
- **Node Types**: 755+ Octane node types supported
- **Icons**: 300+ PNG icons for node types
- **Proto Files**: 30+ API service definitions

---

## 📄 License

OTOY © 2025 - All rights reserved.

Octane Render® and OTOY® are registered trademarks of OTOY Inc.

---

**Last Updated**: 2025-01-29  
**Version**: 1.0.0  
**Status**: Production-ready  
**Recent Changes**: UI refinements (tab bars matching Octane SE), documentation cleanup (24 temp files removed)
