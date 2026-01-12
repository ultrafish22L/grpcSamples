# OctaneWebR - React/TypeScript Octane UI Clone

Modern browser-based interface for OTOY Octane Render with direct gRPC connectivity.

## 🎯 Project Status

**OctaneWebR** is a React 18 + TypeScript + Vite port of octaneWeb, providing real-time interaction with Octane Render through the LiveLink gRPC API.

**Status**: ✅ **Production-Ready Core** - All essential features working, advanced features in progress

### Key Features

- ✅ **Direct gRPC Integration**: Embedded Vite plugin proxy - no separate server process needed
- ✅ **Menu System**: File/Edit/View/Window/Help menus with file dialogs (partial implementation)
- ✅ **Real-time Scene Management**: Interactive scene outliner with hierarchical tree view
- ✅ **Node Inspector**: View and edit node properties with real-time updates to Octane
- ✅ **Parameter Editing**: All types supported (bool, int, float, vectors, colors, enums, strings)
- ✅ **Node Graph Editor**: ReactFlow-based visual node graph with drag-and-drop
- ✅ **Live Rendering**: Real-time callback-based viewport with camera controls (orbit, pan, zoom)
- ✅ **Camera Controls**: Mouse-based orbit/pan/zoom with real-time sync to Octane
- ⏳ **Material Database**: Live DB and Local DB tabs (UI exists, content not implemented)
- ⏳ **Render Toolbar**: UI complete, most actions need API integration
- ✅ **Professional UI**: OTOY-branded dark theme with responsive design
- ✅ **Type Safety**: Full TypeScript support with auto-generated protobuf types

## 🏗️ Architecture

### Component Structure

```
Browser (React App) → Vite Dev Server (gRPC-Web Plugin) → Octane LiveLink (127.0.0.1:51022)
```

**Why No Direct Connection?**
Browsers cannot natively speak gRPC (HTTP/2 binary protocol). The Vite plugin acts as a transparent gRPC-Web proxy embedded in your dev server - this is the industry-standard pattern.

### Technology Stack

#### Frontend
- **React 18** - UI framework with hooks and context
- **TypeScript 5.6** - Type-safe development
- **Vite 6** - Fast build tool with HMR
- **Custom CSS** - OTOY-branded styling (no framework dependencies)

#### Backend Integration
- **gRPC-Web** - Browser-compatible gRPC protocol
- **Protocol Buffers** - Type-safe API contracts
- **Vite Plugin** - Embedded proxy server (no separate process)

#### Key Libraries
- `@grpc/grpc-js` - Node.js gRPC client
- `google-protobuf` - Protobuf runtime
- `grpc-tools` - Code generation from .proto files

## 📁 Project Structure

```
octaneWebR/
├── client/                          # React frontend
│   ├── src/
│   │   ├── components/              # UI components
│   │   │   ├── CallbackRenderViewport.tsx    # Real-time rendering
│   │   │   ├── ConnectionStatus.tsx          # Connection indicator
│   │   │   ├── NodeGraphEditor.tsx           # Visual node graph
│   │   │   ├── NodeInspector.tsx             # Property editor
│   │   │   └── SceneOutliner.tsx             # Scene tree view
│   │   ├── hooks/
│   │   │   └── useOctane.tsx        # Octane client React hook
│   │   ├── services/
│   │   │   └── OctaneClient.ts      # Core gRPC client logic
│   │   ├── types/
│   │   │   └── scene.ts             # TypeScript type definitions
│   │   ├── App.tsx                  # Main application component
│   │   └── main.tsx                 # Application entry point
│   ├── public/                      # Static assets
│   └── index.html                   # HTML template
│
├── server/                          # Build tooling & protobuf generation
│   ├── proto/                       # Octane .proto API definitions
│   ├── generated/                   # Auto-generated TypeScript types
│   ├── vite-plugin-octane-grpc.ts   # Embedded gRPC proxy plugin
│   └── proto-gen.js                 # Protobuf code generator
│
├── scripts/
│   └── start-dev.js                 # Combined dev server launcher
│
├── package.json                     # Dependencies & scripts
├── tsconfig.json                    # TypeScript configuration
├── vite.config.mts                   # Vite build configuration
└── *.md                             # Documentation
```

## 🔌 API Integration

### gRPC Services

OctaneWebR integrates with these Octane LiveLink APIs:

#### Core APIs
- **ApiProjectManager** - Root node access and project management
- **ApiItem** - Node metadata (name, type, attributes)
- **ApiNode** - Node information and properties
- **ApiNodeGraph** - Graph traversal and owned items

#### Rendering APIs
- **LiveLink.RegisterOnNewImageCallback** - Real-time render streaming
- **LiveLink.SetCamera** - Camera synchronization
- **LiveLink.GetCamera** - Camera state retrieval

#### Utility APIs
- **ApiItemArray** - Collection iteration
- **ApiRenderEngine** - Render statistics

### Response Structure Patterns

Different API methods return different response structures:

```typescript
// Most methods return: {result: {handle, type}}
ApiProjectManager.rootNodeGraph() → {result: {handle: "1000000", type: "ApiRootNodeGraph"}}
ApiItem.name() → {result: "teapot.obj"}

// getOwnedItems returns: {list: {handle, type}}
ApiNodeGraph.getOwnedItems() → {list: {handle: "1000001", type: "ApiItemArray"}}
```

## 🎨 UI Components

### Menu Bar ✅
- Complete File/Edit/Script/Module/Cloud/Window/Help menus
- File operations: New, Open, Save, Save As, Recent Projects
- Native browser file dialogs (useFileDialog hook)
- Recent files persistence (localStorage, max 10 files)
- Dynamic submenus with smart positioning
- Keyboard shortcut display
- Integrated with Octane API for file operations

### Scene Outliner ✅
- Hierarchical tree view of Octane scene
- Expand/collapse nodes all the way to end nodes
- Node selection for inspection
- Type icons (Geometry, RenderTarget, etc.) with proper styling
- Three tabs: Scene, Live DB, Local DB

### Node Inspector ✅
- Hierarchical tree view for selected node
- All parameter types: bool, int, float, vectors (2/3/4), colors, enums, strings
- Real-time parameter editing with ApiItem.setByAttrID
- Color picker for AT_FLOAT3 (NT_TEX_RGB)
- Enum dropdown support with proper value/label mapping
- Vector inputs with individual component controls
- TypeScript type safety maintained

### Node Graph Editor ✅
- ReactFlow-based implementation (357 lines, -63% from custom code)
- Professional drag-and-drop, zoom, pan, minimap features
- Custom OctaneNode components with proper pin coloring
- Input pins use pinInfo.pinColor (from Octane API)
- Output pins use nodeInfo.nodeColor (node body color)
- Context menu for node creation (Materials, Geometry, Textures, etc.)
- Bezier spline connections between nodes
- FitView on initial scene load only (preserves user zoom/pan)

### Callback Render Viewport ✅
- Real-time render streaming via WebSocket OnNewImage callbacks
- Mouse drag camera controls (left-click rotate, scroll zoom)
- Automatic camera initialization from Octane on connect
- HDR/LDR automatic format detection with proper buffer isolation
- Canvas-based display with responsive layout
- Frame counter and render status indicators


## 🚀 Development Workflow

### Single Command Start
```bash
npm run dev
```

This starts:
1. Vite dev server with HMR (port 5173 or next available)
2. Embedded gRPC proxy (integrated in Vite)
3. Opens browser to http://localhost:5173

### Development Tools
- **Hot Module Replacement**: Instant updates without page reload
- **TypeScript Checking**: Real-time type validation
- **Source Maps**: Debug original TypeScript in browser DevTools
- **Console Logging**: Comprehensive API call tracking

## 🔧 Build & Deployment

### Development Build
```bash
npm run dev
```

### Production Build
```bash
npm run build
```
Output: `dist/` directory with optimized static files

### Preview Production Build
```bash
npm run preview
```

### Code Generation
```bash
npm run proto:generate
```
Regenerates TypeScript types from .proto files

## 🐛 Development & Debugging

### Debugging Best Practices

**MINIMIZE visual debug sessions** - Prefer builds and log checking:

1. **TypeScript Errors**: Run `npm run build` or `tsc --noEmit` to catch type errors
2. **Runtime Errors**: Check browser console logs (F12) - don't attach debuggers unless necessary
3. **API Issues**: Console logs show 📤 (request) and ✅ (success) markers with full request/response data
4. **Performance**: Use console.time/timeEnd, not profilers for initial checks

**When to use visual debugging**:
- Complex state mutations you can't understand from logs
- Async race conditions that logs don't reveal
- Browser-specific rendering bugs

### Browser Console Logs

All components log extensively with emoji markers:
- 📤 API request sent
- ✅ API success response
- ❌ API error response
- 🔄 Scene tree conversion (Node Graph)
- 📌 Pin detection (Node Graph)
- 🔗 Edge creation (Node Graph)
- 🎨 Rendering events

**Check console FIRST before debugging visually.**

### Common Issues

**Connection Failed**
- Status LED shows red "Disconnected"
- Fix: Ensure Octane running with LiveLink enabled (Help → LiveLink in Octane)
- Fix: Verify port 51022 open: `curl http://localhost:43929/api/health`

**TypeScript Build Errors**
- Run `npm run proto:generate` to regenerate types from .proto files
- Check `server/generated/` for updated type definitions

**ReactFlow Edge Clicks Not Working**
- Status: ✅ Fixed (commit 471bacc9) - CSS `pointer-events: stroke` now enabled
- Edges clickable for deletion/reconnection

## 📝 Code Patterns

### Using the Octane Client

```typescript
// In a component
const { client, isConnected } = useOctane();

// Make API calls
const response = await client.callApi('ApiItem', 'name', {
  handle: nodeHandle,
  type: 16 // ApiItem type
});

// Access response data (pattern varies by method)
const name = response.result; // or response.list, etc.
```

### Adding New API Methods

1. Ensure method exists in `server/proto/*.proto`
2. Run `npm run proto:generate` to update types
3. Use `client.callApi(service, method, params)` pattern
4. Check response structure in browser console logs

## 🔐 Security Notes

- **Localhost Only**: Default configuration binds to 127.0.0.1 only
- **No Authentication**: Inherits Octane LiveLink's security model
- **CORS**: Configured for local development (update for production)

## 🚧 Known Issues & Limitations

### Not Yet Ported from octaneWeb
1. **Material Database**: Live DB and Local DB tabs are placeholders (content not implemented)
2. **Render Toolbar Actions**: ~25 actions need API integration (start/stop/pause rendering, clay mode, picking modes, etc.)
3. **Menu System**: Only 13/40+ menu items fully implemented
   - Missing: cloud.*, module.*, script.*, most file operations
4. **Scene File Loading**: File dialog works but loading not wired to Octane API
5. **Toast Notifications**: User feedback system not built
6. **Keyboard Shortcuts**: Shortcut system not implemented
7. **Camera Presets**: Front/Back/Top/Bottom/Left/Right views not implemented

### General Limitations
1. **Browser-Only**: No native desktop app packaging (yet)
2. **Single Client**: One browser connection per Octane instance
3. **Callback Streaming**: Requires active connection (no offline mode)

## 📚 Related Documentation

- **QUICKSTART.md** - Step-by-step setup and run instructions
- **IMPLEMENTATION_PLAN.md** - Comprehensive feature roadmap (350+ node types, 850+ tasks)
- **CODE_REVIEW.md** - Detailed code quality analysis and recommendations

## 🤝 Development Workflow

**Core Principles**:
1. **Check console logs FIRST** - Don't start debugging visually until you've read all console output
2. **Run builds to check TypeScript errors** - `npm run build` or `tsc --noEmit`
3. **Test with real Octane only** - Never use mock data
4. **Minimize visual debug sessions** - Use only when logs don't reveal the issue

**Before Committing**:
1. Run `npm run build` - Ensure no TypeScript errors
2. Check browser console - No uncaught errors
3. Test with Octane connected - Verify functionality works
4. Update docs if adding features or fixing bugs

**Commit Message Format**:
```
Fix: Brief description of what was fixed

- Detail 1
- Detail 2
- Root cause explanation (if applicable)
```

---

**Version**: 0.9.7  
**Last Updated**: 2025-01-23  
**Recent Changes**:
- Fixed ReactFlow edge clicks with CSS pointer-events (commit 471bacc9)
- Fixed output pin colors to use nodeInfo.nodeColor (commit a1f2be66)


## API Development Guidelines

### Critical: Always Check Proto Files

**Never assume API method names!** Common patterns don't always apply in Octane's gRPC API.

**Example - Node Deletion**:
```typescript
// WRONG (assumed name)
await this.callApi('ApiItem', 'deleteItem', nodeHandle, {});

// CORRECT (verified in proto)
await this.callApi('ApiItem', 'destroy', nodeHandle, {});
```

**Proto files**: `/grpcSamples/octaneProxy/generated/*_pb2_grpc.py`

**Workflow**:
1. Identify required operation (e.g., "delete node")
2. Find proto file (`grep -r "class Api" generated/*.py`)
3. Check service methods (read proto class definition)
4. Verify method name (e.g., `destroy` not `deleteItem`)
5. Implement with correct name

See `OCTANE_API_REFERENCE.md` for complete API documentation.
