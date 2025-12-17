# OctaneWebR - React + TypeScript Port with Direct gRPC

## 🎯 Architecture

```
Browser (React UI) → Node.js Backend (Express + @grpc/grpc-js) → Octane gRPC (127.0.0.1:51022)
```

**No Python proxy required!** This is a complete rewrite of octaneWeb using:
- **Frontend**: React 18 + TypeScript + Vite
- **Backend**: Node.js + Express + @grpc/grpc-js + @grpc/proto-loader
- **State**: Zustand for global state management
- **Styling**: Original octaneWeb CSS (copied and organized)

## 🚀 Quick Start

### Prerequisites
1. **Octane Render** installed and running
2. **LiveLink enabled** in Octane (Help → LiveLink)
3. **Node.js 18+** installed

### Installation
```bash
cd /workspace/grpcSamples/octaneWebR
npm install
```

### Running the Application
```bash
npm run dev
```

This starts:
- **Backend**: http://localhost:45042 (Node.js gRPC server)
- **Frontend**: http://localhost:44479 (Vite dev server)

Open http://localhost:44479 in your browser.

## 📁 Project Structure

```
octaneWebR/
├── src/                        # React TypeScript frontend
│   ├── components/
│   │   ├── layout/             # MenuBar, StatusBar, MainLayout
│   │   └── panels/             # SceneOutliner, RenderViewport, NodeInspector, NodeGraphEditor
│   ├── api/                    # octaneClient.ts (REST wrapper for backend)
│   ├── store/                  # sceneStore.ts (Zustand state management)
│   ├── types/                  # TypeScript interfaces
│   ├── styles/css/             # Copied CSS from octaneWeb
│   ├── App.tsx                 # Main app component
│   └── main.tsx                # React entry point
├── server/
│   └── octaneGrpcServer.ts     # Node.js gRPC backend with Express
├── package.json
├── vite.config.ts              # Vite configuration with API proxy
├── tsconfig.json               # TypeScript configuration
└── README.md                   # This file
```

## 🔌 API Endpoints

### Health Check
```bash
GET /api/health
```

Returns connection status:
```json
{
  "status": "connected",
  "architecture": "Node.js → Direct gRPC → Octane",
  "proxy": "NONE (direct connection)",
  "octane": "127.0.0.1:51022",
  "camera": { ... }
}
```

### Generic gRPC Call
```bash
POST /api/rpc/:service/:method
Content-Type: application/json

{
  "param1": "value1",
  "param2": "value2"
}
```

Examples:
```bash
# Get camera from LiveLink service
curl -X POST http://localhost:45042/api/rpc/LiveLink/GetCamera \
  -H "Content-Type: application/json" \
  -d '{}'

# Build scene tree from GraphServer service
curl -X POST http://localhost:45042/api/rpc/GraphServer/buildSceneTree \
  -H "Content-Type: application/json" \
  -d '{"graphId": 1}'
```

## 🏗️ Component Architecture

### State Management (Zustand)
Global state in `src/store/sceneStore.ts`:
- `connected`: boolean - Connection status to Octane
- `sceneTree`: SceneNode[] - Hierarchical scene tree
- `selectedNode`: SceneNode | null - Currently selected node
- `expandedNodes`: Set<string> - Expanded node IDs
- `searchQuery`: string - Scene search filter

### Components

#### MainLayout
4-panel layout matching octaneWeb:
- Left: Scene Outliner (300px)
- Center Top: Render Viewport (flex)
- Center Bottom: Node Graph Editor (flex)
- Right: Node Inspector (320px)

#### SceneOutliner
- Scene/Link/Local tabs
- Search box with real-time filtering
- Tree view with expand/collapse
- Visibility toggle per node (eye icon)
- Node icons based on type
- Refresh button

#### RenderViewport
- Canvas element for WebGL rendering
- Placeholder when disconnected
- Future: Real-time callback streaming

#### NodeInspector
- Property display for selected node
- Parameter groups (collapsible sections)
- Input controls: text, number, color, dropdown, slider
- Property grid layout

#### NodeGraphEditor
- Canvas for node graph visualization
- Zoom/pan controls (+, -, fit)
- Future: Node creation, connection editing

## 🎨 Styling

All CSS copied from octaneWeb and organized:
- `octane-theme.css` - CSS variables, colors, fonts, base styles
- `layout.css` - Grid layouts, panel sizing, responsive design
- `components.css` - Component-specific styles

Imported in `App.tsx`:
```typescript
import './styles/css/octane-theme.css';
import './styles/css/layout.css';
import './styles/css/components.css';
```

## 🔧 Development

### Available Scripts

```bash
npm run dev            # Start both backend and frontend (recommended)
npm run dev:backend    # Start Node.js backend only (port 45042)
npm run dev:frontend   # Start Vite frontend only (port 44479)
npm run build          # Production build
npm run preview        # Preview production build
```

### Hot Module Replacement (HMR)
Both backend and frontend support hot reloading:
- **Frontend**: Vite HMR (instant React updates)
- **Backend**: tsx watch mode (auto-restart on file changes)

### Debugging

#### Backend Debugging
```bash
# Check if backend is running
curl http://localhost:45042/api/health

# Test gRPC connection
curl -X POST http://localhost:45042/api/rpc/LiveLink/GetCamera \
  -H "Content-Type: application/json" \
  -d '{}'
```

#### Frontend Debugging
Open browser DevTools:
- **React DevTools**: Inspect component hierarchy
- **Network Tab**: Check API calls to `/api/rpc/*`
- **Console**: View frontend logs

## 📊 Proto Loading

The backend dynamically loads all 95 proto files from:
```
/workspace/grpcSamples/sdk/src/api/grpc/protodef/*.proto
```

Creates separate gRPC clients for each service:
- `LiveLink` - Camera, render control, scene info
- `GraphServer` - Scene graph operations
- (Additional services auto-detected)

## 🔄 Migration from octaneWeb

### Key Changes

| octaneWeb | octaneWebR |
|-----------|-----------|
| Vanilla JavaScript | React + TypeScript |
| Python proxy server | Node.js + @grpc/grpc-js |
| Global variables | Zustand state management |
| Programmatic DOM | React components |
| fetch() calls | axios + REST wrapper |
| Inline styles | Imported CSS modules |

### What Was Preserved
✅ Exact UI layout and styling  
✅ All panels and controls  
✅ Scene sync algorithm  
✅ Node inspection logic  
✅ Color scheme and fonts  
✅ User experience

### What Was Improved
🚀 **Direct gRPC**: No Python middleman  
🚀 **Type Safety**: Full TypeScript coverage  
🚀 **State Management**: Centralized with Zustand  
🚀 **Developer Experience**: Hot reload, better debugging  
🚀 **Build System**: Modern Vite tooling  
🚀 **Code Organization**: Component-based architecture

## 🧪 Testing

### Manual Testing Checklist
- [x] Backend starts without errors
- [x] Frontend loads at http://localhost:44479
- [x] UI matches octaneWeb layout
- [ ] Auto-connect on page load (needs Octane running)
- [ ] Scene Outliner loads tree structure (needs Octane)
- [ ] Node selection updates Node Inspector (needs Octane)
- [x] Search filter UI present
- [x] Expand/collapse UI present
- [x] Visibility toggle UI present
- [x] Status bar shows connection status

### Connection Testing
1. **Octane Not Running**:
   - Backend health check returns "disconnected"
   - Frontend shows "Disconnected" status
   - Scene Outliner shows "Connect to Octane to load scene"

2. **Octane Running**:
   - Backend health check returns "connected"
   - Frontend auto-connects
   - Scene tree loads automatically

## 🐛 Troubleshooting

### Backend Won't Start
```bash
# Check if port 45042 is in use
ps aux | grep "45042"

# Kill existing process
kill -9 <PID>

# Restart
npm run dev:backend
```

### Frontend Won't Load
```bash
# Check if port 44479 is in use
ps aux | grep "44479"

# Clear Vite cache
rm -rf node_modules/.vite

# Restart
npm run dev:frontend
```

### Connection Errors
1. Verify Octane is running
2. Enable LiveLink in Octane (Help → LiveLink)
3. Check Octane is on port 51022 (default)
4. Test backend health: `curl http://localhost:45042/api/health`

### CSS Not Loading
1. Check CSS files exist in `src/styles/css/`
2. Verify imports in `App.tsx`
3. Clear browser cache (Ctrl+Shift+R)
4. Check browser console for 404 errors

## 📚 Documentation

See also:
- `/workspace/IMPROVED_MISSION_PROMPT.md` - Detailed implementation guide
- `/workspace/grpcSamples/octaneWeb/` - Original octaneWeb source
- `/workspace/grpcSamples/sdk/src/api/grpc/protodef/` - Proto definitions

## 🎯 Future Enhancements

### Phase 2 Features (Not Yet Implemented)
- [ ] Real-time render streaming (OnNewImage callbacks)
- [ ] Camera manipulation with mouse drag
- [ ] Node graph editing (create nodes, edit connections)
- [ ] Parameter editing in Node Inspector
- [ ] File menu actions (Open, Save, Import)
- [ ] Scene manipulation (Add, Delete, Rename nodes)
- [ ] Material preview
- [ ] Performance optimizations (virtualized tree, canvas caching)

## 🙏 Acknowledgments

This project ports the excellent octaneWeb interface to modern React architecture while preserving its functionality and UX. All credit for the original design and implementation goes to the octaneWeb team.

## 📝 License

Same as octaneWeb and Octane SDK.

---

**Status**: ✅ Core UI and architecture complete, ready for Phase 2 implementation (real-time rendering and interaction)
