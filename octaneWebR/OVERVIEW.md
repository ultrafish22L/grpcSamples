# OctaneWebR - React + TypeScript Octane LiveLink Client

Modern browser-based interface for OTOY Octane Render with direct gRPC connectivity, no separate proxy server required.

## 🎯 Project Overview

**OctaneWebR** is a production-ready web application that provides real-time interaction with OTOY's Octane Render through the LiveLink gRPC API. Built with React 18, TypeScript, and Vite, it delivers a professional rendering workflow with scene management, node inspection, and real-time viewport rendering.

### Key Features

- ✅ **Direct gRPC Integration**: Embedded Vite plugin proxy - no separate server process needed
- ✅ **Real-time Scene Management**: Interactive scene outliner with hierarchical tree view
- ✅ **Node Inspector**: View and edit node properties and attributes
- ✅ **Live Rendering**: Real-time callback-based viewport with HDR/LDR support
- ✅ **Node Graph Editor**: Visual node graph with interactive editing
- ✅ **Material Database Access**: Browse online (Live DB) and local material libraries
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

### Scene Outliner
- Hierarchical tree view of Octane scene
- Expand/collapse nodes all the way to end nodes
- Node selection for inspection
- Type icons (Geometry, RenderTarget, etc.) for non-empty pins 

### Node Inspector
- Hierarchical tree view for selected node
- Attribute viewing and editing
- number slider/arrows, color picker, checkbox, etc.

### Node Graph Editor
- Visual representation of node connections
- Right-click context menus
- Node creation and deletion
- Zoom and pan navigation

### Callback Render Viewport
- Real-time render streaming via callbacks
- HDR/LDR automatic format detection
- Canvas-based display with zoom controls
- Frame counter and performance stats


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

## 🐛 Debugging

### Browser DevTools
- Check Console for API call logs with 📤 (request) and ✅ (success) markers
- Network tab shows HTTP-to-gRPC proxy traffic
- React DevTools for component inspection

### Common Issues

#### Connection Failed
- **Symptom**: "Connection failed" status
- **Fix**: Ensure Octane is running with LiveLink enabled (Help → LiveLink)
- **Fix**: Verify Octane is listening on 127.0.0.1:51022
- **Fix**: stop and alert human to check if octane crashed

#### TypeScript Errors
- **Symptom**: Build fails with type errors
- **Fix**: Run `npm run proto:generate` to regenerate types
- **Fix**: Check `server/generated/` for updated type definitions

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

## 🚧 Known Limitations

1. **Browser-Only**: No native desktop app packaging (yet)
2. **Single Client**: One browser connection per Octane instance
3. **Callback Streaming**: Requires active connection (no offline mode)

## 📚 Related Documentation

- **QUICKSTART.md** - Step-by-step setup and run instructions

## 🤝 Contributing

When making changes:

1. **Run TypeScript checks**: `npm run check`
2. **Update documentation**: Keep these .md files current
3. **Test with real Octane**: Never use mock data
4. **Follow patterns**: Check existing components for style

## 📄 License

Part of the grpcSamples repository - refer to parent repository for licensing.

---

**Status**: ✅ Production Ready  
**Version**: 1.0.0  
**Last Updated**: 2025-01-19
