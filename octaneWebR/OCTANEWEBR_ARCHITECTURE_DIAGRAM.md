# OctaneWebR Architecture Visual Guide

## 🎯 High-Level Architecture Comparison

### Current: octaneWeb (Production)

```
┌─────────────────────────────────────────────────────────────────┐
│                         BROWSER                                 │
│  ┌────────────────────────────────────────────────────────────┐ │
│  │              octaneWeb (Vanilla JavaScript)                 │ │
│  │                                                              │ │
│  │  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐     │ │
│  │  │   Scene      │  │    Node      │  │   Callback   │     │ │
│  │  │  Outliner    │  │  Inspector   │  │  Viewport    │     │ │
│  │  └──────┬───────┘  └──────┬───────┘  └──────┬───────┘     │ │
│  │         │                  │                  │             │ │
│  │         └──────────────────┼──────────────────┘             │ │
│  │                            │                                │ │
│  │                   ┌────────▼────────┐                       │ │
│  │                   │ OctaneWebClient │                       │ │
│  │                   │   (makeApiCall) │                       │ │
│  │                   └────────┬────────┘                       │ │
│  │                            │                                │ │
│  └────────────────────────────┼────────────────────────────────┘ │
│                               │                                  │
└───────────────────────────────┼──────────────────────────────────┘
                                │
                                │ HTTP POST /service/method
                                │ { params: {...} }
                                ▼
┌─────────────────────────────────────────────────────────────────┐
│                    PYTHON PROXY SERVER                          │
│                  octane_proxy.py (Port 51023)                   │
│  ┌────────────────────────────────────────────────────────────┐ │
│  │  1. Parse URL: /ApiProjectManager/getPing                  │ │
│  │  2. Import: apiprojectmanager_pb2_grpc                     │ │
│  │  3. Create stub: ApiProjectManagerStub(channel)            │ │
│  │  4. Get method: stub.getPing                               │ │
│  │  5. Build request: getPingRequest() or Empty()             │ │
│  │  6. Call gRPC: response = method(request)                  │ │
│  │  7. Convert: MessageToDict(response)                       │ │
│  │  8. Return JSON                                             │ │
│  └────────────────────────┬───────────────────────────────────┘ │
│                           │                                      │
│  ┌────────────────────────▼───────────────────────────────────┐ │
│  │        callback_streamer.py (WebSocket)                     │ │
│  │  • Registers OnNewImage callback with Octane                │ │
│  │  • Streams frames to browser via WebSocket                  │ │
│  │  • Handles HDR/LDR buffer conversion                        │ │
│  └────────────────────────┬───────────────────────────────────┘ │
│                           │                                      │
└───────────────────────────┼──────────────────────────────────────┘
                            │
                            │ gRPC (Protocol Buffers)
                            ▼
┌─────────────────────────────────────────────────────────────────┐
│                   OCTANE STANDALONE                             │
│                LiveLink Service (Port 51022)                    │
│  ┌────────────────────────────────────────────────────────────┐ │
│  │  • ApiProjectManager                                        │ │
│  │  • ApiRenderEngineService                                   │ │
│  │  • ApiObjectGraphService                                    │ │
│  │  • [20+ more services...]                                   │ │
│  └────────────────────────────────────────────────────────────┘ │
└─────────────────────────────────────────────────────────────────┘
```

---

### Target: octaneWebR (React TypeScript + Node.js)

```
┌─────────────────────────────────────────────────────────────────┐
│                         BROWSER                                 │
│  ┌────────────────────────────────────────────────────────────┐ │
│  │          octaneWebR (React TypeScript + Vite)               │ │
│  │                                                              │ │
│  │  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐     │ │
│  │  │   Scene      │  │    Node      │  │   Callback   │     │ │
│  │  │  Outliner    │  │  Inspector   │  │  Viewport    │     │ │
│  │  │   .tsx       │  │    .tsx      │  │    .tsx      │     │ │
│  │  └──────┬───────┘  └──────┬───────┘  └──────┬───────┘     │ │
│  │         │                  │                  │             │ │
│  │         └──────────────────┼──────────────────┘             │ │
│  │                            │                                │ │
│  │                   ┌────────▼────────┐                       │ │
│  │                   │ useOctaneClient │                       │ │
│  │                   │   React Hook    │                       │ │
│  │                   └────────┬────────┘                       │ │
│  │                            │                                │ │
│  │                   ┌────────▼────────┐                       │ │
│  │                   │ OctaneClient.ts │                       │ │
│  │                   │  (fetch/WS)     │                       │ │
│  │                   └────────┬────────┘                       │ │
│  │                            │                                │ │
│  └────────────────────────────┼────────────────────────────────┘ │
│                               │                                  │
└───────────────────────────────┼──────────────────────────────────┘
                                │
                                │ HTTP POST /api/grpc/:service/:method
                                │ WebSocket /api/callbacks
                                ▼
┌─────────────────────────────────────────────────────────────────┐
│                 NODE.JS EXPRESS SERVER                          │
│                server/src/index.ts (Port 51024)                 │
│  ┌────────────────────────────────────────────────────────────┐ │
│  │               Express Routes (routes.ts)                    │ │
│  │                                                              │ │
│  │  POST /api/grpc/:service/:method                            │ │
│  │  ├─ Parse params: { service, method }                       │ │
│  │  ├─ Extract body: params                                    │ │
│  │  └─ Call: grpcClient.callMethod(service, method, params)    │ │
│  │                                                              │ │
│  │  WebSocket /api/callbacks                                   │ │
│  │  ├─ On connect: Register OnNewImage callback                │ │
│  │  ├─ On message: Handle client requests                      │ │
│  │  └─ On disconnect: Unregister callbacks                     │ │
│  └────────────────────────┬───────────────────────────────────┘ │
│                           │                                      │
│  ┌────────────────────────▼───────────────────────────────────┐ │
│  │          OctaneGrpcClient (grpc/client.ts)                  │ │
│  │                                                              │ │
│  │  class OctaneGrpcClient {                                   │ │
│  │    private channel: grpc.Channel;                           │ │
│  │    private services: Map<string, ServiceStub>;              │ │
│  │                                                              │ │
│  │    async initialize() {                                     │ │
│  │      // Load .proto files with @grpc/proto-loader           │ │
│  │      packageDef = protoLoader.loadSync(protoFiles);         │ │
│  │      protoDesc = grpc.loadPackageDefinition(packageDef);    │ │
│  │    }                                                         │ │
│  │                                                              │ │
│  │    async callMethod(service, method, params) {              │ │
│  │      // Get or create service stub                          │ │
│  │      stub = this.getService(service);                       │ │
│  │      // Make gRPC call                                      │ │
│  │      return new Promise((resolve, reject) => {              │ │
│  │        stub[method](params, (err, response) => {            │ │
│  │          if (err) reject(err);                              │ │
│  │          else resolve(response);                            │ │
│  │        });                                                   │ │
│  │      });                                                     │ │
│  │    }                                                         │ │
│  │  }                                                           │ │
│  └────────────────────────┬───────────────────────────────────┘ │
│                           │                                      │
└───────────────────────────┼──────────────────────────────────────┘
                            │
                            │ gRPC (@grpc/grpc-js)
                            │ Protocol Buffers
                            ▼
┌─────────────────────────────────────────────────────────────────┐
│                   OCTANE STANDALONE                             │
│                LiveLink Service (Port 51022)                    │
│  ┌────────────────────────────────────────────────────────────┐ │
│  │  • ApiProjectManager                                        │ │
│  │  • ApiRenderEngineService                                   │ │
│  │  • ApiObjectGraphService                                    │ │
│  │  • [20+ more services...]                                   │ │
│  └────────────────────────────────────────────────────────────┘ │
└─────────────────────────────────────────────────────────────────┘
```

---

## 🔄 Data Flow Comparison

### Example: Setting Camera Position

#### Current Flow (octaneWeb)

```
User drags mouse in viewport
       │
       ▼
CallbackRenderViewport.js
  • Calculate new camera position
  • mouse event → camera math
       │
       ▼
client.setCameraPosition(x, y, z)
       │
       ▼
OctaneWebClient.js → makeApiCall()
       │
       ▼
fetch('http://localhost:51023/ApiRenderEngineService/setCameraPosition', {
  method: 'POST',
  body: JSON.stringify({ position: {x, y, z} })
})
       │
       ▼
octane_proxy.py
  • Parse URL: service=ApiRenderEngineService, method=setCameraPosition
  • Import: apirenderengineservice_pb2_grpc
  • Create: ApiRenderEngineServiceStub(channel)
  • Build: SetCameraPositionRequest(position=Vector3(x, y, z))
  • Call: stub.setCameraPosition(request)
       │
       ▼
Octane gRPC → Camera updated → New frame rendered → Callback
       │
       ▼
callback_streamer.py
  • Receives OnNewImage event
  • Converts HDR buffer
  • Sends via WebSocket
       │
       ▼
CallbackRenderViewport.js
  • Receives frame data
  • Updates WebGL texture
  • Renders to canvas
```

#### Target Flow (octaneWebR)

```
User drags mouse in viewport
       │
       ▼
CallbackRenderViewport.tsx
  • Calculate new camera position
  • mouse event → camera math
  • useState + useEffect
       │
       ▼
const { client } = useOctaneClient()
client.setCameraPosition(x, y, z)
       │
       ▼
OctaneClient.ts → makeApiCall()
       │
       ▼
fetch('http://localhost:51024/api/grpc/ApiRenderEngineService/setCameraPosition', {
  method: 'POST',
  headers: { 'Content-Type': 'application/json' },
  body: JSON.stringify({ position: {x, y, z} })
})
       │
       ▼
Node.js Express: POST /api/grpc/:service/:method
  • Extract: service = ApiRenderEngineService
  • Extract: method = setCameraPosition
  • Extract: params = { position: {x, y, z} }
       │
       ▼
grpcClient.callMethod('ApiRenderEngineService', 'setCameraPosition', params)
       │
       ▼
OctaneGrpcClient.ts
  • Get service stub: getService('ApiRenderEngineService')
  • Create request with TypeScript types
  • Call: stub.setCameraPosition(request, callback)
       │
       ▼
Octane gRPC → Camera updated → New frame rendered → Callback
       │
       ▼
websocket.ts (WebSocket server)
  • Receives OnNewImage event
  • Converts to JSON
  • Sends to WebSocket clients
       │
       ▼
useCallbackStream() hook
  • WebSocket connection
  • Receives frame data
  • useState to trigger re-render
       │
       ▼
CallbackRenderViewport.tsx
  • useEffect on frame change
  • Updates WebGL texture
  • Renders to canvas
```

**Key Differences:**
1. React hooks manage component lifecycle
2. TypeScript provides type safety
3. Single Node.js process (no Python)
4. Same gRPC protocol to Octane
5. Same WebSocket pattern for callbacks

---

## 📊 Component Hierarchy

### octaneWebR Component Tree

```
App.tsx (Root)
│
├─ OctaneClientProvider (Context)
│  │
│  ├─ MenuSystem
│  │  └─ File, Edit, View, Help menus
│  │
│  └─ LayoutManager
│     │
│     ├─ CallbackRenderViewport
│     │  ├─ useCallbackStream()
│     │  ├─ useCamera()
│     │  └─ <canvas ref={canvasRef} />
│     │
│     ├─ SceneOutliner
│     │  ├─ useOctaneClient()
│     │  └─ TreeView (recursive)
│     │     └─ TreeNode
│     │        ├─ ExpandButton
│     │        ├─ NodeIcon
│     │        ├─ NodeName
│     │        ├─ VisibilityToggle
│     │        └─ TreeNode[] (children)
│     │
│     ├─ NodeInspector
│     │  ├─ useOctaneClient()
│     │  └─ PropertyEditor
│     │     └─ PropertyControl (for each property)
│     │        ├─ FloatInput
│     │        ├─ BoolCheckbox
│     │        ├─ EnumSelect
│     │        ├─ ColorPicker
│     │        └─ TextureSelect
│     │
│     ├─ NodeGraphEditor
│     │  ├─ ReactFlow
│     │  ├─ CustomNodes
│     │  ├─ ContextMenu
│     │  └─ NodeCreator
│     │
│     └─ RenderToolbar
│        ├─ StartButton
│        ├─ StopButton
│        ├─ PauseButton
│        ├─ RestartButton
│        ├─ ResetCameraButton
│        └─ RenderStatus
│           ├─ FPS Display
│           ├─ Samples Display
│           └─ Time Display
```

---

## 🔧 Technology Stack Mapping

### Frontend

| Aspect | octaneWeb | octaneWebR |
|--------|-----------|------------|
| **Language** | Vanilla JavaScript | TypeScript |
| **Framework** | None | React 18+ |
| **Build Tool** | None (direct load) | Vite |
| **State Management** | EventSystem + StateManager classes | React Context + hooks |
| **Component Model** | Class-based, DOM manipulation | Functional components, JSX |
| **Styling** | Plain CSS | CSS Modules or styled-components |
| **Type Safety** | None | Full TypeScript |
| **Dev Experience** | Manual refresh | HMR (Hot Module Replacement) |

### Backend

| Aspect | octaneWeb | octaneWebR |
|--------|-----------|------------|
| **Language** | Python 3.x | TypeScript/Node.js |
| **Server Framework** | aiohttp (async) | Express |
| **gRPC Library** | grpcio | @grpc/grpc-js |
| **Protocol Buffers** | Python generated code | TypeScript generated code |
| **WebSocket** | aiohttp WebSocket | ws library |
| **Async Model** | asyncio | Promises/async-await |
| **Type Safety** | Partial (type hints) | Full TypeScript |

### Communication

| Aspect | octaneWeb | octaneWebR |
|--------|-----------|------------|
| **Browser → Backend** | HTTP POST (fetch) | HTTP POST (fetch) |
| **Backend → Octane** | gRPC (Python) | gRPC (Node.js) |
| **Real-time Updates** | WebSocket | WebSocket |
| **Data Format** | JSON | JSON |
| **Port (Backend)** | 51023 | 51024 (or configurable) |
| **Port (Octane)** | 51022 | 51022 (same) |

---

## 📁 File Structure Mapping

### octaneWeb → octaneWebR

```
octaneWeb/                           octaneWebR/
├── index.html                  →   client/index.html
├── js/                              client/src/
│   ├── app.js                  →   ├── main.tsx (entry)
│   │                                ├── App.tsx (main component)
│   ├── core/                        ├── services/
│   │   ├── OctaneWebClient.js  →   │   ├── OctaneClient.ts
│   │   ├── EventSystem.js      →   │   (Context API replaces this)
│   │   └── StateManager.js     →   │   (Context API replaces this)
│   ├── components/                  ├── components/
│   │   ├── CallbackRenderViewport.js → CallbackRenderViewport.tsx
│   │   ├── SceneOutlinerSync.js     → SceneOutliner.tsx
│   │   ├── NodeInspector.js         → NodeInspector.tsx
│   │   ├── NodeGraphEditor.js       → NodeGraphEditor.tsx
│   │   ├── RenderToolbar.js         → RenderToolbar.tsx
│   │   └── MenuSystem.js            → MenuSystem.tsx
│   ├── utils/                       ├── utils/
│   │   ├── Camera.js           →   │   ├── camera.ts
│   │   ├── GenericNodeRenderer.js → │   ├── propertyControls.tsx
│   │   └── LayoutManager.js         → (react-resizable-panels)
│   └── constants/                   ├── constants/
│       └── octaneNodeTypes.js  →   │   └── nodeTypes.ts
├── css/                             ├── styles/
│   ├── octane-theme.css        →   │   ├── theme.module.css
│   ├── components.css          →   │   ├── components.module.css
│   └── layout.css              →   │   └── layout.module.css
└── shared/                          └── hooks/
    └── webgl-utils.js          →       ├── useOctaneClient.ts
                                         ├── useCallbackStream.ts
                                         └── useCamera.ts

octaneProxy/                         octaneWebR/server/
├── octane_proxy.py             →   ├── src/
│                                    │   ├── index.ts (Express server)
│                                    │   ├── grpc/
│                                    │   │   ├── client.ts (OctaneGrpcClient)
│                                    │   │   └── services.ts
│                                    │   ├── api/
│                                    │   │   ├── routes.ts
│                                    │   │   └── websocket.ts
│                                    │   └── generated/ (from .proto)
├── callback_streamer.py        →   └── proto/ (copied from sdk/)
└── generated/
    └── *_pb2.py                →   server/src/generated/*_pb.ts
```

---

## 🎯 State Management Comparison

### octaneWeb: Event-Driven State

```javascript
// EventSystem.js - Event bus
class EventSystem {
  listeners = new Map();
  
  on(event, callback) {
    this.listeners.get(event).add(callback);
  }
  
  emit(event, data) {
    this.listeners.get(event).forEach(cb => cb(data));
  }
}

// StateManager.js - Centralized state
class StateManager {
  state = {
    sceneState: {},
    renderState: {},
    nodeGraphState: {}
  };
  
  setState(key, value) {
    this.state[key] = value;
    this.eventSystem.emit(`${key}Updated`, value);
  }
}

// Component usage
class SceneOutliner {
  constructor(eventSystem, stateManager) {
    this.eventSystem = eventSystem;
    this.stateManager = stateManager;
    
    this.eventSystem.on('sceneStateUpdated', (sceneState) => {
      this.render(sceneState);
    });
  }
}
```

### octaneWebR: React Context + Hooks

```typescript
// OctaneClientContext.tsx - React Context
interface OctaneContextType {
  client: OctaneClient;
  sceneState: SceneState;
  renderState: RenderState;
  isConnected: boolean;
}

const OctaneContext = createContext<OctaneContextType | null>(null);

export function OctaneClientProvider({ children }) {
  const [client] = useState(() => new OctaneClient());
  const [sceneState, setSceneState] = useState<SceneState>({});
  const [renderState, setRenderState] = useState<RenderState>({});
  
  useEffect(() => {
    client.on('sceneUpdate', setSceneState);
    client.on('renderUpdate', setRenderState);
    return () => {
      client.off('sceneUpdate', setSceneState);
      client.off('renderUpdate', setRenderState);
    };
  }, [client]);
  
  return (
    <OctaneContext.Provider value={{ client, sceneState, renderState }}>
      {children}
    </OctaneContext.Provider>
  );
}

// Custom hook
export function useOctaneClient() {
  return useContext(OctaneContext);
}

// Component usage
export function SceneOutliner() {
  const { sceneState } = useOctaneClient();
  
  // Component automatically re-renders when sceneState changes
  return <TreeView nodes={sceneState.hierarchy} />;
}
```

---

## 🚀 Build & Development Workflow

### octaneWeb Development

```bash
# Terminal 1: Start Python proxy
cd octaneProxy
python octane_proxy.py

# Terminal 2: Start web server
cd octaneWeb
python -m http.server 43331

# Browser
open http://localhost:43331
```

### octaneWebR Development

```bash
# One-time setup
cd octaneWebR
npm install
npm run generate:proto

# Development (single command starts both)
npm run dev
# This runs:
#   • Vite dev server (client) on port 5173
#   • Node.js server (backend) on port 51024
#   • Both with hot reload

# Or separate terminals
# Terminal 1: Backend
npm run server:dev

# Terminal 2: Frontend
npm run client:dev

# Browser
open http://localhost:5173
```

### octaneWebR Production Build

```bash
npm run build
# Builds:
#   • client/dist/ - optimized React bundle
#   • server/dist/ - compiled TypeScript

npm run start
# Runs production server serving client bundle
```

---

## 🎨 CSS Architecture

### octaneWeb

```
octane-theme.css (2000+ lines, much unused)
  ├─ Global styles
  ├─ Component styles (some unused)
  └─ Utility classes

components.css
  └─ Component-specific overrides

layout.css
  └─ Panel layouts

JavaScript creates DOM programmatically:
  element.className = 'scene-outliner-item active'
```

### octaneWebR

```
Extracted minimal CSS → CSS Modules

theme.module.css (500 lines, all used)
  └─ Only classes actually used

components.module.css
  └─ Component-specific styles

layout.module.css
  └─ Layout utilities

TypeScript/React declarative:
  <div className={styles.sceneOutlinerItem + 
    (isActive ? styles.active : '')}>
```

---

## ✅ Success Criteria Visualization

```
┌─────────────────────────────────────────────────────────┐
│  SUCCESS = octaneWebR looks and works like octaneWeb   │
└─────────────────────────────────────────────────────────┘
                           │
          ┌────────────────┴────────────────┐
          │                                 │
    ┌─────▼─────┐                    ┌─────▼─────┐
    │  VISUAL   │                    │ FUNCTIONAL │
    │  FIDELITY │                    │  PARITY    │
    └─────┬─────┘                    └─────┬──────┘
          │                                 │
    ┌─────┴─────┬─────┬─────┬─────┐        ├─────┬─────┬─────┐
    │           │     │     │     │        │     │     │     │
┌───▼───┐   ┌──▼──┐ ┌▼──┐ ┌▼──┐ ┌▼──┐  ┌──▼──┐ ┌▼──┐ ┌▼──┐ ┌▼──┐
│Colors │   │Fonts│ │Lay│ │Spac│ │Icon│  │Scene│ │Node│ │Rend│ │Cam│
│  ✓    │   │  ✓  │ │ ✓ │ │ ✓  │ │ ✓  │  │  ✓  │ │ ✓  │ │ ✓  │ │ ✓ │
└───────┘   └─────┘ └───┘ └────┘ └────┘  └─────┘ └────┘ └────┘ └───┘
 Same        Same    Same  Same   Same    Works   Works  Works  Works
 #colors     fonts   panels gaps  icons   same    same   same   same
```

---

## 🔄 Migration Checklist Matrix

| Original File | Target File | Status | Dependencies | Priority |
|---------------|-------------|--------|--------------|----------|
| app.js | main.tsx, App.tsx | ⬜ | None | 🔴 High |
| OctaneWebClient.js | OctaneClient.ts | ⬜ | grpc client | 🔴 High |
| CallbackRenderViewport.js | CallbackRenderViewport.tsx | ⬜ | WebSocket | 🔴 High |
| SceneOutlinerSync.js | SceneOutliner.tsx | ⬜ | OctaneClient | 🟡 Medium |
| NodeInspector.js | NodeInspector.tsx | ⬜ | OctaneClient | 🟡 Medium |
| NodeGraphEditor.js | NodeGraphEditor.tsx | ⬜ | OctaneClient | 🟡 Medium |
| RenderToolbar.js | RenderToolbar.tsx | ⬜ | OctaneClient | 🟡 Medium |
| MenuSystem.js | MenuSystem.tsx | ⬜ | None | 🟢 Low |
| LayoutManager.js | LayoutManager.tsx | ⬜ | Components | 🟡 Medium |
| octane_proxy.py | grpc/client.ts | ⬜ | Proto files | 🔴 High |
| callback_streamer.py | api/websocket.ts | ⬜ | grpc client | 🔴 High |

Legend: ⬜ Not started | 🟦 In progress | ✅ Complete

---

This architecture guide provides visual clarity for the entire migration. Reference it alongside the other documents for a complete understanding of the project structure! 🚀
